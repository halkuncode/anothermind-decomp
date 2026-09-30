package rank

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"path/filepath"
	"regexp"
	"sort"
	"strings"

	"github.com/halkuncode/anothermind-decomp/tools/builder/builder"
)

type entry struct {
	score        float32
	instructions int
	name         string
	path         string
}

func Rank(target string, topCount int) error {
	version := builder.Version()
	asmBase := filepath.Join("asm", version, "nonmatchings")

	if _, err := os.Stat(asmBase); os.IsNotExist(err) {
		return fmt.Errorf("assembly directory '%s' not found. Please run './mako.sh build' first", asmBase)
	}

	searchPath := asmBase
	if target != "" {
		target = strings.TrimPrefix(target, "src/")
		target = strings.TrimSuffix(target, ".c")

		candidate1 := filepath.Join(asmBase, target)
		candidate2 := filepath.Join("asm", version, target)
		candidate3 := target

		if info, err := os.Stat(candidate1); err == nil && info.IsDir() {
			searchPath = candidate1
		} else if info, err := os.Stat(candidate2); err == nil && info.IsDir() {
			searchPath = candidate2
		} else if _, err := os.Stat(candidate3); err == nil {
			searchPath = candidate3
		} else {
			return fmt.Errorf("could not find nonmatching assembly for '%s' (checked %s)", target, candidate1)
		}
	}

	var entries []entry
	err := filepath.Walk(searchPath, func(path string, _ os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if !strings.HasSuffix(path, ".s") {
			return nil
		}
		if !strings.Contains(path, "nonmatchings") {
			return nil
		}
		score, instrs, err := rankFunction(path)
		if err != nil {
			return err
		}
		if instrs == 0 {
			return nil
		}
		rel, _ := filepath.Rel(".", path)
		entries = append(entries, entry{
			score:        score,
			instructions: instrs,
			name:         strings.TrimSuffix(filepath.Base(path), ".s"),
			path:         rel,
		})
		return nil
	})
	if err != nil {
		return err
	}

	if len(entries) == 0 {
		fmt.Println("No nonmatching functions found.")
		return nil
	}

	sort.Slice(entries, func(i, j int) bool {
		if entries[i].instructions != entries[j].instructions {
			return entries[i].instructions < entries[j].instructions
		}
		if entries[i].score != entries[j].score {
			return entries[i].score < entries[j].score
		}
		return entries[i].name < entries[j].name
	})

	count := len(entries)
	if topCount > 0 && topCount < count {
		count = topCount
	}

	header := fmt.Sprintf("Top %d easiest nonmatching functions", count)
	if target != "" {
		header += fmt.Sprintf(" in %s", target)
	}
	fmt.Printf("%s (out of %d total):\n", header, len(entries))
	fmt.Printf("%-5s  %-6s  %-6s  %-30s  %s\n", "Rank", "Score", "Instrs", "Function", "Path")
	fmt.Println(strings.Repeat("-", 80))
	for i := 0; i < count; i++ {
		e := entries[i]
		fmt.Printf("%-5d  %-6.3f  %-6d  %-30s  %s\n", i+1, e.score, e.instructions, e.name, e.path)
	}
	return nil
}

// NOTE: decompilationDifficultyScore and rankFunction are directly converted
// from https://github.com/cdlewis/snowboardkids2-decomp/blob/main/CLAUDE.md
// all rights reserved to the original author https://github.com/cdlewis
// Read more in this article from the same author:
// https://blog.chrislewis.au/the-unexpected-effectiveness-of-one-shot-decompilation-with-claude/

// decompilationDifficultyScore calculates the ML-based difficulty score
// Based on the Python implementation's logistic regression model
func decompilationDifficultyScore(instructions, branches, jumps, labels int) float32 {
	// Standardization parameters (from training)
	means := []float64{34.27065527065527, 1.6666666666666667, 3.1880341880341883, 1.98005698005698}
	stds := []float64{24.763225638334454, 2.047860394102145, 3.200600790997309, 2.3803926026229827}

	// Model coefficients
	coefficients := []float64{2.499706543629367, -0.46648920346754463, -1.61606926820365, 0.4911494991317799}
	intercept := -0.5155412977000488

	// Calculate score
	features := []float64{float64(instructions), float64(branches), float64(jumps), float64(labels)}

	// Standardize features
	logit := intercept
	for i := 0; i < 4; i++ {
		featuresScaled := (features[i] - means[i]) / stds[i]
		logit += featuresScaled * coefficients[i]
	}

	// Sigmoid function
	difficulty := 1.0 / (1.0 + math.Exp(-logit))
	return float32(difficulty)
}

func rankFunction(path string) (float32, int, error) {
	filename := filepath.Base(path)
	funcName := strings.TrimSuffix(filename, ".s")

	// Skip non-code sections (data, bss, rodata, header)
	if strings.HasPrefix(funcName, "jtbl_") ||
		strings.HasPrefix(funcName, "D_") ||
		strings.HasSuffix(funcName, ".data") ||
		strings.HasSuffix(funcName, ".bss") ||
		strings.HasSuffix(funcName, ".rodata") ||
		funcName == "header" {
		return 0, 0, nil
	}

	file, err := os.Open(path)
	if err != nil {
		return 0, 0, err
	}
	defer file.Close()

	branchPattern := regexp.MustCompile(`\b(beq|bne|bnez|beqz|blez|bgtz|bltz|bgez|blt|bgt|ble|bge|bltzal|bgezal)\b`)
	jumpJalPattern := regexp.MustCompile(`\bjal\b`)
	jumpJPattern := regexp.MustCompile(`\bj\b`)
	labelPattern := regexp.MustCompile(`^\s*\.L[0-9A-Fa-f_]+:`)
	instructionPattern := regexp.MustCompile(`/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/`)

	instructionCount := 0
	branchCount := 0
	jumpCount := 0
	labelCount := 0

	scanner := bufio.NewScanner(file)
	var content strings.Builder
	for scanner.Scan() {
		content.WriteString(scanner.Text())
		content.WriteString("\n")
	}
	if err := scanner.Err(); err != nil {
		return 0, 0, err
	}

	contentStr := content.String()

	// Skip files that only contain rodata (no actual code)
	if strings.Contains(contentStr, ".section .rodata") && !strings.Contains(contentStr, "glabel") {
		return 0, 0, nil
	}

	scanner = bufio.NewScanner(strings.NewReader(contentStr))
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())

		if line == "" ||
			strings.HasPrefix(line, "glabel") ||
			strings.HasPrefix(line, "endlabel") ||
			strings.HasPrefix(line, "nonmatching") {
			continue
		}

		if labelPattern.MatchString(line) {
			labelCount++
			continue
		}

		if instructionPattern.MatchString(line) {
			instructionCount++

			if branchPattern.MatchString(line) {
				branchCount++
			}

			if jumpJalPattern.MatchString(line) || jumpJPattern.MatchString(line) {
				jumpCount++
			}
		}
	}

	if err := scanner.Err(); err != nil {
		return 0, 0, err
	}

	if instructionCount == 0 {
		return 0, 0, nil
	}

	score := decompilationDifficultyScore(instructionCount, branchCount, jumpCount, labelCount)
	return score, instructionCount, nil
}

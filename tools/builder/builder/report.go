package builder

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/halkuncode/anothermind-decomp/tools/builder/deps"
)

type fileStats struct {
	relPath    string
	total      int
	decompiled int
}

type moduleStats struct {
	total      int
	decompiled int
	files      []fileStats
}

// Report prints a terminal summary comparing decompiled functions against remaining INCLUDE_ASM stubs.
func Report(version string) error {
	if version == "" {
		version = Version()
	}

	nonmatchingsDir := filepath.Join("asm", version, "nonmatchings")
	matchingsDir := filepath.Join("asm", version, "matchings")

	if _, err := os.Stat(nonmatchingsDir); os.IsNotExist(err) {
		return fmt.Errorf("assembly directory '%s' not found. Please run './mako.sh build' first", nonmatchingsDir)
	}

	modules := make(map[string]*moduleStats)

	err := filepath.Walk("src", func(path string, _ os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if !strings.HasSuffix(path, ".c") {
			return nil
		}

		rel, _ := filepath.Rel("src", path)
		parts := strings.Split(rel, string(filepath.Separator))
		mod := "root"
		if len(parts) > 1 {
			mod = parts[0]
		}

		if _, exists := modules[mod]; !exists {
			modules[mod] = &moduleStats{}
		}

		// Count INCLUDE_ASM in the .c file
		file, err := os.Open(path)
		if err != nil {
			return err
		}
		defer file.Close()

		includeAsmCount := 0
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if strings.HasPrefix(line, "INCLUDE_ASM(") {
				includeAsmCount++
			}
		}

		// Collect all known function stubs from both matchings and nonmatchings
		dir := filepath.Dir(rel)
		stem := strings.TrimSuffix(filepath.Base(path), ".c")
		allFuncs := make(map[string]struct{})

		matchFolder := filepath.Join(matchingsDir, dir, stem)
		if entries, err := os.ReadDir(matchFolder); err == nil {
			for _, e := range entries {
				if !e.IsDir() && strings.HasSuffix(e.Name(), ".s") {
					allFuncs[e.Name()] = struct{}{}
				}
			}
		}

		nonmatchFolder := filepath.Join(nonmatchingsDir, dir, stem)
		if entries, err := os.ReadDir(nonmatchFolder); err == nil {
			for _, e := range entries {
				if !e.IsDir() && strings.HasSuffix(e.Name(), ".s") {
					allFuncs[e.Name()] = struct{}{}
				}
			}
		}

		fileTotal := len(allFuncs)
		decompiledCount := fileTotal - includeAsmCount
		if decompiledCount < 0 {
			decompiledCount = 0
		}
		if fileTotal < includeAsmCount {
			fileTotal = includeAsmCount
		}

		modules[mod].total += fileTotal
		modules[mod].decompiled += decompiledCount
		modules[mod].files = append(modules[mod].files, fileStats{
			relPath:    rel,
			total:      fileTotal,
			decompiled: decompiledCount,
		})
		return nil
	})
	if err != nil {
		return err
	}

	totalAll := 0
	decompAll := 0
	var modNames []string
	for name, m := range modules {
		modNames = append(modNames, name)
		totalAll += m.total
		decompAll += m.decompiled
	}
	sort.Strings(modNames)

	pctAll := float32(0)
	if totalAll > 0 {
		pctAll = float32(decompAll) / float32(totalAll) * 100
	}

	fmt.Printf("Decompiled: %d / %d functions (%.2f%%)\n\n", decompAll, totalAll, pctAll)

	for _, name := range modNames {
		m := modules[name]
		modPct := float32(0)
		if m.total > 0 {
			modPct = float32(m.decompiled) / float32(m.total) * 100
		}
		fmt.Printf("  %-10s: %4d / %4d functions (%6.2f%%)\n", name, m.decompiled, m.total, modPct)

		sort.Slice(m.files, func(i, j int) bool {
			return m.files[i].relPath < m.files[j].relPath
		})
		for _, f := range m.files {
			if f.decompiled > 0 {
				filePct := float32(0)
				if f.total > 0 {
					filePct = float32(f.decompiled) / float32(f.total) * 100
				}
				fmt.Printf("    - %-25s: %3d / %3d (%5.1f%%)\n", f.relPath, f.decompiled, f.total, filePct)
			}
		}
	}

	return nil
}

// ReportJSON generates the objdiff-cli JSON progress report for CI / web tracking
func ReportJSON(version string, outputFile string) error {
	data, _ := os.ReadFile(ConfigPath(version))
	var b BuildConfig
	if err := yaml.Unmarshal(data, &b); err != nil {
		panic(err)
	}
	b.BuildPath = filepath.Join("report", b.BuildPath)
	if err := os.MkdirAll(b.BuildPath, 0755); err != nil {
		return err
	}
	if err := writeObjdiffConfig(b); err != nil {
		return err
	}
	if err := writeSplatConfigs(b); err != nil {
		return err
	}
	if err := writeSha1Check(b); err != nil {
		return err
	}
	_ = os.Setenv("ANOTHERMIND_PROGRESS_REPORT", "1")
	if err := deps.GenNinja(b.BuildPath); err != nil {
		return err
	}
	_ = os.Unsetenv("ANOTHERMIND_PROGRESS_REPORT")
	if err := deps.Ninja(); err != nil {
		return err
	}
	return deps.ObjdiffCLI("report", "generate", "-o", outputFile)
}

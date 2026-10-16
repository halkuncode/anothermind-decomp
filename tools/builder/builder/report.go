package builder

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"sort"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/halkuncode/anothermind-decomp/tools/builder/deps"
)

type fileStats struct {
	relPath    string
	total      int
	decompiled int
	ignored    bool
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

	ignoreRules := LoadIgnoreRules(nil)
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

		if mod == "lib" {
			return nil
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

		ignored := IsFileIgnored(rel, ignoreRules)
		if !ignored {
			modules[mod].total += fileTotal
			modules[mod].decompiled += decompiledCount
		}

		modules[mod].files = append(modules[mod].files, fileStats{
			relPath:    rel,
			total:      fileTotal,
			decompiled: decompiledCount,
			ignored:    ignored,
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

	var outputBuf strings.Builder
	var moduleBuf strings.Builder

	fmt.Fprintf(&outputBuf, "Decompiled: %d / %d functions (%.2f%%)\n\n", decompAll, totalAll, pctAll)

	for idx, name := range modNames {
		if idx > 0 {
			outputBuf.WriteString("\n")
			moduleBuf.WriteString("\n")
		}
		m := modules[name]
		modPct := float32(0)
		if m.total > 0 {
			modPct = float32(m.decompiled) / float32(m.total) * 100
		}
		line := fmt.Sprintf("  %-10s: %4d / %4d functions (%6.2f%%)\n", name, m.decompiled, m.total, modPct)
		outputBuf.WriteString(line)
		moduleBuf.WriteString(line)

		sort.Slice(m.files, func(i, j int) bool {
			return m.files[i].relPath < m.files[j].relPath
		})
		for _, f := range m.files {
			var fileLine string
			if f.ignored {
				fileLine = fmt.Sprintf("    - %-25s: [System library - Excluded]\n", f.relPath)
			} else {
				filePct := float32(0)
				if f.total > 0 {
					filePct = float32(f.decompiled) / float32(f.total) * 100
				}
				fileLine = fmt.Sprintf("    - %-25s: %3d / %3d (%5.1f%%)\n", f.relPath, f.decompiled, f.total, filePct)
			}
			outputBuf.WriteString(fileLine)
			moduleBuf.WriteString(fileLine)
		}
	}

	fmt.Print(outputBuf.String())

	if err := saveMarkdownReport(moduleBuf.String(), decompAll, totalAll, pctAll); err != nil {
		return err
	}
	if err := updateReadmeProgress(modNames, modules); err != nil {
		return err
	}

	return nil
}

func saveMarkdownReport(moduleText string, decompAll, totalAll int, pctAll float32) error {
	dir := filepath.Join("docs", "md_reference")
	if err := os.MkdirAll(dir, 0755); err != nil {
		return err
	}
	content := fmt.Sprintf("# Decompilation Progress Report\n\n```text\nDecompiled: %d / %d functions (%.2f%%)\n\n%s```\n",
		decompAll, totalAll, pctAll, moduleText)
	return os.WriteFile(filepath.Join(dir, "report.md"), []byte(content), 0644)
}

func generateProgressBarSVG(pct float32, width, height int) string {
	fillWidth := int(float32(width) * (pct / 100.0))
	if fillWidth > width {
		fillWidth = width
	}
	if fillWidth < 0 {
		fillWidth = 0
	}
	rx := height / 2

	var fillRect string
	if fillWidth > 0 {
		fillRect = fmt.Sprintf(`<rect width="%d" height="%d" fill="url(#bar-grad)" clip-path="url(#bar-clip)"/>`, fillWidth, height)
	}

	return fmt.Sprintf(`<svg xmlns="http://www.w3.org/2000/svg" width="%d" height="%d" viewBox="0 0 %d %d">
  <defs>
    <linearGradient id="bar-grad" x1="0" y1="0" x2="1" y2="0">
      <stop offset="0%%" stop-color="#3fb950"/>
      <stop offset="100%%" stop-color="#2ea043"/>
    </linearGradient>
    <clipPath id="bar-clip">
      <rect width="%d" height="%d" rx="%d"/>
    </clipPath>
  </defs>
  <rect width="%d" height="%d" rx="%d" fill="#21262d" stroke="#30363d" stroke-width="1"/>
  %s
</svg>
`, width, height, width, height, width, height, rx, width, height, rx, fillRect)
}

func formatModuleName(name string) string {
	switch name {
	case "main":
		return "Main"
	case "kernel":
		return "Kernel"
	case "vm_engine":
		return "VM Engine"
	case "engine":
		return "Engine"
	default:
		parts := strings.Split(name, "_")
		for i, p := range parts {
			if len(p) > 0 {
				parts[i] = strings.ToUpper(p[:1]) + p[1:]
			}
		}
		return strings.Join(parts, " ")
	}
}

func updateReadmeProgress(modNames []string, modules map[string]*moduleStats) error {
	readmePath := "README.md"
	readmeBytes, err := os.ReadFile(readmePath)
	if err != nil {
		return nil
	}
	readmeContent := string(readmeBytes)

	picsDir := filepath.Join("docs", "pics")
	if err := os.MkdirAll(picsDir, 0755); err != nil {
		return err
	}

	var moduleItems strings.Builder
	for _, name := range modNames {
		m := modules[name]
		modPct := float32(0)
		if m.total > 0 {
			modPct = float32(m.decompiled) / float32(m.total) * 100
		}
		displayName := formatModuleName(name)
		svgFilename := fmt.Sprintf("progress_%s.svg", name)
		svgPath := filepath.Join(picsDir, svgFilename)
		svgContent := generateProgressBarSVG(modPct, 260, 16)
		if err := os.WriteFile(svgPath, []byte(svgContent), 0644); err != nil {
			return err
		}

		fmt.Fprintf(&moduleItems, "      <p>\n        <strong>%s</strong>: %d / %d functions (%.2f%%)<br>\n        <img src=\"docs/pics/%s\" alt=\"%s Progress\" width=\"260\" height=\"16\">\n      </p>\n",
			displayName, m.decompiled, m.total, modPct, svgFilename, displayName)
	}

	progressBlock := fmt.Sprintf(`<!-- PROGRESS_START -->
<table>
  <tr>
    <td width="340" align="center" valign="middle">
      <img src="docs/pics/Another_Mind_Coverart.png" alt="Another Mind Cover Art" width="320">
    </td>
    <td valign="middle">
%s      <p>
        <a href="docs/md_reference/report.md">See full stats</a>
      </p>
    </td>
  </tr>
</table>
<!-- PROGRESS_END -->`, moduleItems.String())

	startTag := "<!-- PROGRESS_START -->"
	endTag := "<!-- PROGRESS_END -->"
	startIdx := strings.Index(readmeContent, startTag)
	endIdx := strings.Index(readmeContent, endTag)

	var newReadme string
	if startIdx != -1 && endIdx != -1 && endIdx > startIdx {
		newReadme = readmeContent[:startIdx] + progressBlock + readmeContent[endIdx+len(endTag):]
	} else {
		re := regexp.MustCompile(`(?s)<p align="center">\s*<img src="docs/pics/Another_Mind_Coverart\.png"[^>]*>\s*</p>`)
		if re.MatchString(readmeContent) {
			newReadme = re.ReplaceAllString(readmeContent, progressBlock)
		} else {
			headingIdx := strings.Index(readmeContent, "\n")
			if headingIdx != -1 {
				newReadme = readmeContent[:headingIdx+1] + "\n" + progressBlock + "\n" + readmeContent[headingIdx+1:]
			} else {
				newReadme = progressBlock + "\n\n" + readmeContent
			}
		}
	}

	return os.WriteFile(readmePath, []byte(newReadme), 0644)
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

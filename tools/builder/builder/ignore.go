package builder

import (
	"bufio"
	"os"
	"path/filepath"
	"strings"
)

// LoadIgnoreRules loads exclusion rules from ignore files and CLI overrides.
func LoadIgnoreRules(cliExcludes []string) []string {
	var rules []string
	rules = append(rules, cliExcludes...)

	ignoreFile := filepath.Join("config", "ignored_libraries.txt")
	file, err := os.Open(ignoreFile)
	if err == nil {
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if line == "" || strings.HasPrefix(line, "#") {
				continue
			}
			rules = append(rules, line)
		}
		file.Close()
	}

	return rules
}

// IsFileIgnored returns whether a source file (e.g. "main/psxsdk.c") matches any ignore rule.
func IsFileIgnored(relPath string, rules []string) bool {
	cleanPath := filepath.ToSlash(relPath)
	stem := strings.TrimSuffix(filepath.Base(cleanPath), filepath.Ext(cleanPath))
	for _, rule := range rules {
		rule = strings.TrimSpace(rule)
		if rule == "" {
			continue
		}
		cleanRule := strings.Trim(filepath.ToSlash(rule), "/")
		cleanRuleNoExt := strings.TrimSuffix(cleanRule, filepath.Ext(cleanRule))
		if cleanRule == "" {
			continue
		}
		// Exact file stem match (e.g. rule "psxsdk" matches "main/psxsdk.c")
		if stem == cleanRule || stem == cleanRuleNoExt {
			return true
		}
		// Path match (e.g. rule "main/psxsdk" matches "main/psxsdk.c")
		if cleanPath == cleanRule || cleanPath == cleanRule+".c" ||
			strings.HasPrefix(cleanPath, cleanRule+"/") ||
			strings.HasSuffix(cleanPath, "/"+cleanRule) ||
			strings.HasSuffix(cleanPath, "/"+cleanRule+".c") ||
			strings.Contains(cleanPath, "/"+cleanRule+"/") {
			return true
		}
		if strings.Contains(cleanPath, cleanRule) {
			return true
		}
		if matched, _ := filepath.Match(rule, stem); matched {
			return true
		}
		if matched, _ := filepath.Match(rule, cleanPath); matched {
			return true
		}
	}
	return false
}

// IsIgnored matches function name or path against ignore rules (used by rank).
func IsIgnored(path string, funcName string, rules []string) bool {
	cleanPath := filepath.ToSlash(path)
	for _, rule := range rules {
		rule = strings.TrimSpace(rule)
		if rule == "" {
			continue
		}
		// Exact function name match
		if funcName == rule {
			return true
		}
		// Match path segments or substring (e.g. "psxsdk", "main/psxsdk")
		cleanRule := strings.Trim(filepath.ToSlash(rule), "/")
		if cleanRule != "" {
			if strings.Contains(cleanPath, "/"+cleanRule+"/") ||
				strings.HasSuffix(cleanPath, "/"+cleanRule) ||
				strings.HasPrefix(cleanPath, cleanRule+"/") ||
				cleanPath == cleanRule {
				return true
			}
			if strings.Contains(cleanPath, cleanRule) {
				return true
			}
		}
		// Glob pattern match
		if matched, _ := filepath.Match(rule, funcName); matched {
			return true
		}
		if matched, _ := filepath.Match(rule, cleanPath); matched {
			return true
		}
	}
	return false
}


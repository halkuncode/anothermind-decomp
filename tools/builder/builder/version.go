package builder

import "os"

func Version() string {
	version := os.Getenv("VERSION")
	if version == "" {
		return "jp"
	}
	return version
}

package main

import (
	"fmt"
	"os"

	"github.com/halkuncode/anothermind-decomp/tools/builder/cmd"
)

func main() {
	if err := cmd.Execute(); err != nil {
		_, _ = fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

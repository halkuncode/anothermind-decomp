package cmd

import (
	"github.com/halkuncode/anothermind-decomp/tools/builder/builder"
	"github.com/spf13/cobra"
)

var reportCmd = &cobra.Command{
	Use:   "report [version] [output.json]",
	Short: "Generates a decompilation progress report",
	Args:  cobra.MaximumNArgs(2),
	RunE: func(cmd *cobra.Command, args []string) error {
		if len(args) == 2 {
			return builder.ReportJSON(args[0], args[1])
		}
		version := ""
		if len(args) == 1 {
			version = args[0]
		}
		return builder.Report(version)
	},
}

func init() {
	rootCmd.AddCommand(reportCmd)
}

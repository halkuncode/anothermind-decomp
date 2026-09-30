package cmd

import (
	"github.com/halkuncode/anothermind-decomp/tools/builder/rank"
	"github.com/spf13/cobra"
)

var topCount int

var rankCmd = &cobra.Command{
	Use:   "rank [source_path]",
	Short: "Rank non-decompiled functions from easiest to hardest",
	Args:  cobra.MaximumNArgs(1),
	RunE: func(cmd *cobra.Command, args []string) error {
		path := ""
		if len(args) > 0 {
			path = args[0]
		}
		return rank.Rank(path, topCount)
	},
}

func init() {
	rankCmd.Flags().IntVarP(&topCount, "top", "n", 5, "Number of top easiest functions to display (0 for all)")
	rootCmd.AddCommand(rankCmd)
}

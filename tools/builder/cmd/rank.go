package cmd

import (
	"github.com/halkuncode/anothermind-decomp/tools/builder/rank"
	"github.com/spf13/cobra"
)

var (
	topCount int
	excludes []string
)

var rankCmd = &cobra.Command{
	Use:   "rank [source_path]",
	Short: "Rank non-decompiled functions from easiest to hardest",
	Args:  cobra.MaximumNArgs(1),
	RunE: func(cmd *cobra.Command, args []string) error {
		path := ""
		if len(args) > 0 {
			path = args[0]
		}
		return rank.Rank(path, topCount, excludes)
	},
}

func init() {
	rankCmd.Flags().IntVarP(&topCount, "top", "n", 5, "Number of top easiest functions to display (0 for all)")
	rankCmd.Flags().StringSliceVarP(&excludes, "exclude", "x", nil, "Exclude functions, directories, or patterns (comma-separated or repeatable)")
	rootCmd.AddCommand(rankCmd)
}

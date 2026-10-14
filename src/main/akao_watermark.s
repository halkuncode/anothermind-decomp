.text

/*
 * Square Co. (SC) Akao Sound Driver Build Stamp:
 *
 * Word 1 (0x25097350): Standard 32-bit DOS/FAT datetime
 *   - Date: 0x2509 -> 1998-08-09 (August 9, 1998)
 *   - Time: 0x7350 -> 14:26:32   (2:26:32 PM)
 *
 * Word 2 (0x0043539B): Driver revision & company signature
 *   - 0x9B: Revision / build number (155)
 *   - "SC\0" (0x53, 0x43, 0x00): "Square Co."
 *
 * Embedded at the tail of the .text section of the Akao driver
 * immediately preceding psxsdk.
 */
.word 0x25097350
.word 0x0043539B

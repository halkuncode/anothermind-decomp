SECTIONS
{
    __romPos = 0;
    _gp = 0x80061A1C;
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header : AT(header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        header_s = .;
        build/jp/asm/jp/header.s.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    main_ROM_START = __romPos;
    main_VRAM = ADDR(.main);
    .main 0x80010000 : AT(main_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        main_RODATA_START = .;
        build/jp/asm/jp/data/800.rodata.s.o(.rodata);
        build/jp/src/main/main.c.o(.rodata);
        build/jp/src/main/name_entry.c.o(.rodata);
        build/jp/src/main/chapter_title.c.o(.rodata);
        build/jp/src/main/title.c.o(.rodata);
        build/jp/src/main/cd_stream.c.o(.rodata);
        build/jp/src/main/script.c.o(.rodata);
        build/jp/src/main/akao.c.o(.rodata);
        build/jp/src/main/psxsdk.c.o(.rodata);
        build/jp/src/main/movie.c.o(.rodata);
        . = ALIGN(., 4);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
        main_TEXT_START = .;
        build/jp/src/main/main.c.o(.text);
        build/jp/src/main/name_entry.c.o(.text);
        build/jp/src/main/chapter_title.c.o(.text);
        build/jp/src/main/title.c.o(.text);
        build/jp/src/main/cd_stream.c.o(.text);
        build/jp/src/main/script.c.o(.text);
        build/jp/src/main/akao.c.o(.text);
        build/jp/src/main/psxsdk.c.o(.text);
        build/jp/src/main/movie.c.o(.text);
        . = ALIGN(., 4);
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        _800_rodata__s = .;
        build/jp/asm/jp/data/800.rodata.s.o(.data);
        main_main_c = .;
        build/jp/src/main/main.c.o(.data);
        main_name_entry_c = .;
        build/jp/src/main/name_entry.c.o(.data);
        main_chapter_title_c = .;
        build/jp/src/main/chapter_title.c.o(.data);
        main_title_c = .;
        build/jp/src/main/title.c.o(.data);
        main_cd_stream_c = .;
        build/jp/src/main/cd_stream.c.o(.data);
        main_script_c = .;
        build/jp/src/main/script.c.o(.data);
        main_akao_c = .;
        build/jp/src/main/akao.c.o(.data);
        main_psxsdk_c = .;
        build/jp/src/main/psxsdk.c.o(.data);
        main_movie_c = .;
        build/jp/src/main/movie.c.o(.data);
        _39FD8_data__s = .;
        build/jp/asm/jp/data/39FD8.data.s.o(.data);
        . = ALIGN(., 4);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_SDATA_START = .;
        build/jp/asm/jp/data/5221C.sdata.s.o(.sdata);
        . = ALIGN(., 4);
        main_SDATA_END = .;
        main_SDATA_SIZE = ABSOLUTE(main_SDATA_END - main_SDATA_START);
        main_SBSS_START = .;
        build/jp/asm/jp/data/527B8.sbss.s.o(.sbss);
        . = ALIGN(., 4);
        main_SBSS_END = .;
        main_SBSS_SIZE = ABSOLUTE(main_SBSS_END - main_SBSS_START);
        main_BSS_START = .;
        build/jp/asm/jp/data/800.rodata.s.o(.bss);
        build/jp/src/main/main.c.o(.bss);
        build/jp/src/main/name_entry.c.o(.bss);
        build/jp/src/main/chapter_title.c.o(.bss);
        build/jp/src/main/title.c.o(.bss);
        build/jp/src/main/cd_stream.c.o(.bss);
        build/jp/src/main/script.c.o(.bss);
        build/jp/src/main/akao.c.o(.bss);
        build/jp/src/main/psxsdk.c.o(.bss);
        build/jp/src/main/movie.c.o(.bss);
        build/jp/asm/jp/data/527C0.bss.s.o(.bss);
        . = ALIGN(., 4);
        main_BSS_END = .;
        main_BSS_SIZE = ABSOLUTE(main_BSS_END - main_BSS_START);
    }
    __romPos += SIZEOF(.main);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    main_ROM_END = __romPos;
    main_VRAM_END = .;

    engine_ROM_START = __romPos;
    engine_VRAM = ADDR(.engine);
    .engine 0x800E4BB0 : AT(engine_ROM_START) SUBALIGN(4)
    {
        FILL(0x00000000);
        engine_RODATA_START = .;
        build/jp/asm/jp/data/D53B0.rodata.s.o(.rodata);
        build/jp/src/engine/vram_cache.c.o(.rodata);
        build/jp/src/engine/portrait_anim.c.o(.rodata);
        build/jp/src/engine/taiwa.c.o(.rodata);
        build/jp/src/engine/demo_menu.c.o(.rodata);
        build/jp/src/engine/memcard.c.o(.rodata);
        build/jp/src/engine/portrait_select.c.o(.rodata);
        build/jp/src/engine/game_loop.c.o(.rodata);
        . = ALIGN(., 4);
        engine_RODATA_END = .;
        engine_RODATA_SIZE = ABSOLUTE(engine_RODATA_END - engine_RODATA_START);
        engine_TEXT_START = .;
        build/jp/src/engine/vram_cache.c.o(.text);
        build/jp/src/engine/portrait_anim.c.o(.text);
        build/jp/src/engine/taiwa.c.o(.text);
        build/jp/src/engine/demo_menu.c.o(.text);
        build/jp/src/engine/memcard.c.o(.text);
        build/jp/src/engine/portrait_select.c.o(.text);
        build/jp/src/engine/game_loop.c.o(.text);
        . = ALIGN(., 4);
        engine_TEXT_END = .;
        engine_TEXT_SIZE = ABSOLUTE(engine_TEXT_END - engine_TEXT_START);
        engine_DATA_START = .;
        D53B0_rodata__s = .;
        build/jp/asm/jp/data/D53B0.rodata.s.o(.data);
        engine_vram_cache_c = .;
        build/jp/src/engine/vram_cache.c.o(.data);
        engine_portrait_anim_c = .;
        build/jp/src/engine/portrait_anim.c.o(.data);
        engine_taiwa_c = .;
        build/jp/src/engine/taiwa.c.o(.data);
        engine_demo_menu_c = .;
        build/jp/src/engine/demo_menu.c.o(.data);
        engine_memcard_c = .;
        build/jp/src/engine/memcard.c.o(.data);
        engine_portrait_select_c = .;
        build/jp/src/engine/portrait_select.c.o(.data);
        engine_game_loop_c = .;
        build/jp/src/engine/game_loop.c.o(.data);
        FD390_data__s = .;
        build/jp/asm/jp/data/FD390.data.s.o(.data);
        . = ALIGN(., 4);
        engine_DATA_END = .;
        engine_DATA_SIZE = ABSOLUTE(engine_DATA_END - engine_DATA_START);
        engine_BSS_START = .;
        build/jp/asm/jp/data/D53B0.rodata.s.o(.bss);
        build/jp/src/engine/vram_cache.c.o(.bss);
        build/jp/src/engine/portrait_anim.c.o(.bss);
        build/jp/src/engine/taiwa.c.o(.bss);
        build/jp/src/engine/demo_menu.c.o(.bss);
        build/jp/src/engine/memcard.c.o(.bss);
        build/jp/src/engine/portrait_select.c.o(.bss);
        build/jp/src/engine/game_loop.c.o(.bss);
        build/jp/asm/jp/data/FD9B0.bss.s.o(.bss);
        . = ALIGN(., 4);
        engine_BSS_END = .;
        engine_BSS_SIZE = ABSOLUTE(engine_BSS_END - engine_BSS_START);
    }
    __romPos += SIZEOF(.engine);
    __romPos = ALIGN(__romPos, 4);
    . = ALIGN(., 4);
    engine_ROM_END = __romPos;
    engine_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}

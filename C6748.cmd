/****************************************************************************/
/*  C6748.cmd                                                               */
/*  Copyright (c) 2010 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on a C6748               */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/
-stack 0x400
MEMORY
{
    DSPL2ROM     o = 0x00700000  l = 0x00100000   /* 1MB L2 Internal ROM */
    DSPL2RAM_BOOT     o = 0x00800000  l = 0x00001000   /* 256kB L2 Internal RAM */
    DSPL2RAM_PRO        o = 0x00801000  l = 0x0003F000   /* 256kB L2 Internal RAM */
    DSPL1PRAM    o = 0x00E00000  l = 0x00008000   /* 32kB L1 Internal Program RAM */
    DSPL1DRAM    o = 0x00F00000  l = 0x00008000   /* 32kB L1 Internal Data RAM */
    SHDSPL2ROM   o = 0x11700000  l = 0x00100000   /* 1MB L2 Shared Internal ROM */
    SHDSPL2RAM   o = 0x11800000  l = 0x00040000   /* 256kB L2 Shared Internal RAM */
    SHDSPL1PRAM  o = 0x11E00000  l = 0x00008000   /* 32kB L1 Shared Internal Program RAM */
    SHDSPL1DRAM  o = 0x11F00000  l = 0x00008000   /* 32kB L1 Shared Internal Data RAM */
    EMIFACS0     o = 0x40000000  l = 0x20000000   /* 512MB SDRAM Data (CS0) */
    EMIFACS2     o = 0x60000000  l = 0x02000000   /* 32MB Async Data (CS2) */
    EMIFACS3     o = 0x62000000  l = 0x02000000   /* 32MB Async Data (CS3) */
    EMIFACS4     o = 0x64000000  l = 0x02000000   /* 32MB Async Data (CS4) */
    EMIFACS5     o = 0x66000000  l = 0x02000000   /* 32MB Async Data (CS5) */
    SHRAM        o = 0x80000000  l = 0x00020000   /* 128kB Shared RAM */
    DDR2         o = 0xC0000000  l = 0x20000000   /* 512MB DDR2 Data */
}                                              
                                               
SECTIONS                                       
{                                              
    // .text          >  SHRAM        /* text:��ִ�д����,�������п�ִ�еĴ���,�Լ���������������ĳ���*/
    /* Program memory (PAGE 0) sections */
    .text1     : {main.obj(.text)}> DSPL2RAM_BOOT /*���������ڵ�.obj��������һ���Σ����õ�H0*/

    .text2     : {*(.text)}> DSPL2RAM_PRO /*ʣ���.obj������һ���Σ����õ�*/
    .stack         >  DSPL2RAM_PRO     /* stack:ջ�Σ��ɷ���SHRAM����DSPL2RAM����,����DSPL2RAM��������и��� */
    .bss           >  DSPL2RAM_PRO        /* bss: Ϊȫ�ֺ;�̬���������洢�ռ�*/     //SHRAM
    .cio           >  DSPL2RAM_PRO
    .const         >  DSPL2RAM_PRO     /* const: �������ַ����������ַ������֡�ѡ����Լ�ʹ��const�ؼ��ֶ���(���ǲ�����volatile���ͣ�������ʹ��С�ڴ�ģ��)��ֻ���ͱ���*/
    .data          >  SHRAM
    .switch        >  DSPL2RAM_PRO     /* switch: ���switch-caseָ����ʹ�õ�ѡ���*/
    .sysmem        >  DSPL2RAM_PRO     /* sysmem: Ϊ��̬�ڴ���䱣���洢�ռ䣬�Ӷ�Ϊmalloc��calloc��realloc�� new�ȶ�̬�ڴ���������� */
    .far           >  DSPL2RAM_PRO
    .args          >  DSPL2RAM_PRO
    .ppinfo        >  DSPL2RAM_PRO
    .ppdata        >  DSPL2RAM_PRO
  
    /* COFF sections */
    .pinit         >  SHRAM     /*pinit,cinit: �����˳�ʼ�������ͳ������õı��*/
    .cinit         >  SHRAM
  
    /* EABI sections */
    .binit         >  DSPL2RAM_PRO
    .init_array    >  DSPL2RAM_PRO
    .neardata      >  DSPL2RAM_PRO
    .fardata       >  DSPL2RAM_PRO
    .rodata        >  DSPL2RAM_PRO
    .c6xabi.exidx  >  DSPL2RAM_PRO
    .c6xabi.extab  >  DSPL2RAM_PRO
}

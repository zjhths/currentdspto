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
    // .text          >  SHRAM        /* text:可执行代码段,包含所有可执行的代码,以及编译器编译产生的常量*/
    /* Program memory (PAGE 0) sections */
    .text1     : {main.obj(.text)}> DSPL2RAM_BOOT /*主函数所在的.obj单独放在一个段，配置到H0*/

    .text2     : {*(.text)}> DSPL2RAM_PRO /*剩余的.obj放在另一个段，配置到*/
    .stack         >  DSPL2RAM_PRO     /* stack:栈段，可放在SHRAM或者DSPL2RAM里面,放在DSPL2RAM里，程序运行更快 */
    .bss           >  DSPL2RAM_PRO        /* bss: 为全局和静态变量保留存储空间*/     //SHRAM
    .cio           >  DSPL2RAM_PRO
    .const         >  DSPL2RAM_PRO     /* const: 包含了字符串常量、字符串文字、选择表以及使用const关键字定义(但是不包括volatile类型，并假设使用小内存模型)的只读型变量*/
    .data          >  SHRAM
    .switch        >  DSPL2RAM_PRO     /* switch: 存放switch-case指令所使用的选择表*/
    .sysmem        >  DSPL2RAM_PRO     /* sysmem: 为动态内存分配保留存储空间，从而为malloc，calloc，realloc和 new等动态内存分配程序服务 */
    .far           >  DSPL2RAM_PRO
    .args          >  DSPL2RAM_PRO
    .ppinfo        >  DSPL2RAM_PRO
    .ppdata        >  DSPL2RAM_PRO
  
    /* COFF sections */
    .pinit         >  SHRAM     /*pinit,cinit: 包含了初始化变量和常量所用的表格*/
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

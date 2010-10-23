/*
 * Remmina - The GTK+ Remote Desktop Client
 * Copyright (C) 2010 Vic Lee
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, 
 * Boston, MA 02111-1307, USA.
 */

/* rdp ui functions, run inside the rdp thread */

#include "remminapluginrdp.h"
#include "remminapluginrdpev.h"
#include "remminapluginrdpui.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <gdk/gdkx.h>

typedef guchar (*RemminaROP3Func) (guchar p, guchar s, guchar d);

/* ------------ Generated codes from genrop3.c  ----------------- */
static guchar remmina_rop3_00 (guchar p, guchar s, guchar d) { return 0; }
static guchar remmina_rop3_01 (guchar p, guchar s, guchar d) { return ~(((s | p) | d)); }
static guchar remmina_rop3_02 (guchar p, guchar s, guchar d) { return (~((s | p)) & d); }
static guchar remmina_rop3_03 (guchar p, guchar s, guchar d) { return ~((s | p)); }
static guchar remmina_rop3_04 (guchar p, guchar s, guchar d) { return (~((p | d)) & s); }
static guchar remmina_rop3_05 (guchar p, guchar s, guchar d) { return ~((p | d)); }
static guchar remmina_rop3_06 (guchar p, guchar s, guchar d) { return ~((~((s ^ d)) | p)); }
static guchar remmina_rop3_07 (guchar p, guchar s, guchar d) { return ~(((s & d) | p)); }
static guchar remmina_rop3_08 (guchar p, guchar s, guchar d) { return ((~(p) & d) & s); }
static guchar remmina_rop3_09 (guchar p, guchar s, guchar d) { return ~(((s ^ d) | p)); }
static guchar remmina_rop3_0a (guchar p, guchar s, guchar d) { return (~(p) & d); }
static guchar remmina_rop3_0b (guchar p, guchar s, guchar d) { return ~(((~(d) & s) | p)); }
static guchar remmina_rop3_0c (guchar p, guchar s, guchar d) { return (~(p) & s); }
static guchar remmina_rop3_0d (guchar p, guchar s, guchar d) { return ~(((~(s) & d) | p)); }
static guchar remmina_rop3_0e (guchar p, guchar s, guchar d) { return ~((~((s | d)) | p)); }
static guchar remmina_rop3_0f (guchar p, guchar s, guchar d) { return ~(p); }
static guchar remmina_rop3_10 (guchar p, guchar s, guchar d) { return (~((s | d)) & p); }
static guchar remmina_rop3_11 (guchar p, guchar s, guchar d) { return ~((s | d)); }
static guchar remmina_rop3_12 (guchar p, guchar s, guchar d) { return ~((~((p ^ d)) | s)); }
static guchar remmina_rop3_13 (guchar p, guchar s, guchar d) { return ~(((p & d) | s)); }
static guchar remmina_rop3_14 (guchar p, guchar s, guchar d) { return ~((~((s ^ p)) | d)); }
static guchar remmina_rop3_15 (guchar p, guchar s, guchar d) { return ~(((s & p) | d)); }
static guchar remmina_rop3_16 (guchar p, guchar s, guchar d) { return (((~((s & p)) & d) ^ s) ^ p); }
static guchar remmina_rop3_17 (guchar p, guchar s, guchar d) { return ~((((s ^ d) & (p ^ s)) ^ s)); }
static guchar remmina_rop3_18 (guchar p, guchar s, guchar d) { return ((d ^ p) & (p ^ s)); }
static guchar remmina_rop3_19 (guchar p, guchar s, guchar d) { return ~(((~((s & p)) & d) ^ s)); }
static guchar remmina_rop3_1a (guchar p, guchar s, guchar d) { return (((p & s) | d) ^ p); }
static guchar remmina_rop3_1b (guchar p, guchar s, guchar d) { return ~((((s ^ p) & d) ^ s)); }
static guchar remmina_rop3_1c (guchar p, guchar s, guchar d) { return (((p & d) | s) ^ p); }
static guchar remmina_rop3_1d (guchar p, guchar s, guchar d) { return ~((((d ^ p) & s) ^ d)); }
static guchar remmina_rop3_1e (guchar p, guchar s, guchar d) { return ((s | d) ^ p); }
static guchar remmina_rop3_1f (guchar p, guchar s, guchar d) { return ~(((s | d) & p)); }
static guchar remmina_rop3_20 (guchar p, guchar s, guchar d) { return ((~(s) & p) & d); }
static guchar remmina_rop3_21 (guchar p, guchar s, guchar d) { return ~(((p ^ d) | s)); }
static guchar remmina_rop3_22 (guchar p, guchar s, guchar d) { return (~(s) & d); }
static guchar remmina_rop3_23 (guchar p, guchar s, guchar d) { return ~(((~(d) & p) | s)); }
static guchar remmina_rop3_24 (guchar p, guchar s, guchar d) { return ((s ^ d) & (p ^ s)); }
static guchar remmina_rop3_25 (guchar p, guchar s, guchar d) { return ~(((~((p & s)) & d) ^ p)); }
static guchar remmina_rop3_26 (guchar p, guchar s, guchar d) { return (((s & p) | d) ^ s); }
static guchar remmina_rop3_27 (guchar p, guchar s, guchar d) { return ((~((s ^ p)) | d) ^ s); }
static guchar remmina_rop3_28 (guchar p, guchar s, guchar d) { return ((s ^ p) & d); }
static guchar remmina_rop3_29 (guchar p, guchar s, guchar d) { return ~(((((s & p) | d) ^ s) ^ p)); }
static guchar remmina_rop3_2a (guchar p, guchar s, guchar d) { return (~((s & p)) & d); }
static guchar remmina_rop3_2b (guchar p, guchar s, guchar d) { return ~((((d ^ p) & (p ^ s)) ^ s)); }
static guchar remmina_rop3_2c (guchar p, guchar s, guchar d) { return (((s | d) & p) ^ s); }
static guchar remmina_rop3_2d (guchar p, guchar s, guchar d) { return ((~(d) | s) ^ p); }
static guchar remmina_rop3_2e (guchar p, guchar s, guchar d) { return (((p ^ d) | s) ^ p); }
static guchar remmina_rop3_2f (guchar p, guchar s, guchar d) { return ~(((~(d) | s) & p)); }
static guchar remmina_rop3_30 (guchar p, guchar s, guchar d) { return (~(s) & p); }
static guchar remmina_rop3_31 (guchar p, guchar s, guchar d) { return ~(((~(p) & d) | s)); }
static guchar remmina_rop3_32 (guchar p, guchar s, guchar d) { return (((s | p) | d) ^ s); }
static guchar remmina_rop3_33 (guchar p, guchar s, guchar d) { return ~(s); }
static guchar remmina_rop3_34 (guchar p, guchar s, guchar d) { return (((s & d) | p) ^ s); }
static guchar remmina_rop3_35 (guchar p, guchar s, guchar d) { return ((~((s ^ d)) | p) ^ s); }
static guchar remmina_rop3_36 (guchar p, guchar s, guchar d) { return ((p | d) ^ s); }
static guchar remmina_rop3_37 (guchar p, guchar s, guchar d) { return ~(((p | d) & s)); }
static guchar remmina_rop3_38 (guchar p, guchar s, guchar d) { return (((p | d) & s) ^ p); }
static guchar remmina_rop3_39 (guchar p, guchar s, guchar d) { return ((~(d) | p) ^ s); }
static guchar remmina_rop3_3a (guchar p, guchar s, guchar d) { return (((s ^ d) | p) ^ s); }
static guchar remmina_rop3_3b (guchar p, guchar s, guchar d) { return ~(((~(d) | p) & s)); }
static guchar remmina_rop3_3c (guchar p, guchar s, guchar d) { return (s ^ p); }
static guchar remmina_rop3_3d (guchar p, guchar s, guchar d) { return ((~((s | d)) | p) ^ s); }
static guchar remmina_rop3_3e (guchar p, guchar s, guchar d) { return (((~(s) & d) | p) ^ s); }
static guchar remmina_rop3_3f (guchar p, guchar s, guchar d) { return ~((s & p)); }
static guchar remmina_rop3_40 (guchar p, guchar s, guchar d) { return ((~(d) & s) & p); }
static guchar remmina_rop3_41 (guchar p, guchar s, guchar d) { return ~(((s ^ p) | d)); }
static guchar remmina_rop3_42 (guchar p, guchar s, guchar d) { return ((d ^ p) & (d ^ s)); }
static guchar remmina_rop3_43 (guchar p, guchar s, guchar d) { return ~(((~((s & d)) & p) ^ s)); }
static guchar remmina_rop3_44 (guchar p, guchar s, guchar d) { return (~(d) & s); }
static guchar remmina_rop3_45 (guchar p, guchar s, guchar d) { return ~(((~(s) & p) | d)); }
static guchar remmina_rop3_46 (guchar p, guchar s, guchar d) { return (((d & p) | s) ^ d); }
static guchar remmina_rop3_47 (guchar p, guchar s, guchar d) { return ~((((p ^ d) & s) ^ p)); }
static guchar remmina_rop3_48 (guchar p, guchar s, guchar d) { return ((p ^ d) & s); }
static guchar remmina_rop3_49 (guchar p, guchar s, guchar d) { return ~(((((d & p) | s) ^ d) ^ p)); }
static guchar remmina_rop3_4a (guchar p, guchar s, guchar d) { return (((d | s) & p) ^ d); }
static guchar remmina_rop3_4b (guchar p, guchar s, guchar d) { return ((~(s) | d) ^ p); }
static guchar remmina_rop3_4c (guchar p, guchar s, guchar d) { return (~((p & d)) & s); }
static guchar remmina_rop3_4d (guchar p, guchar s, guchar d) { return ~((((s ^ d) | (p ^ s)) ^ s)); }
static guchar remmina_rop3_4e (guchar p, guchar s, guchar d) { return (((p ^ s) | d) ^ p); }
static guchar remmina_rop3_4f (guchar p, guchar s, guchar d) { return ~(((~(s) | d) & p)); }
static guchar remmina_rop3_50 (guchar p, guchar s, guchar d) { return (~(d) & p); }
static guchar remmina_rop3_51 (guchar p, guchar s, guchar d) { return ~(((~(p) & s) | d)); }
static guchar remmina_rop3_52 (guchar p, guchar s, guchar d) { return (((d & s) | p) ^ d); }
static guchar remmina_rop3_53 (guchar p, guchar s, guchar d) { return ~((((s ^ d) & p) ^ s)); }
static guchar remmina_rop3_54 (guchar p, guchar s, guchar d) { return ~((~((s | p)) | d)); }
static guchar remmina_rop3_55 (guchar p, guchar s, guchar d) { return ~(d); }
static guchar remmina_rop3_56 (guchar p, guchar s, guchar d) { return ((s | p) ^ d); }
static guchar remmina_rop3_57 (guchar p, guchar s, guchar d) { return ~(((s | p) & d)); }
static guchar remmina_rop3_58 (guchar p, guchar s, guchar d) { return (((p | s) & d) ^ p); }
static guchar remmina_rop3_59 (guchar p, guchar s, guchar d) { return ((~(s) | p) ^ d); }
static guchar remmina_rop3_5a (guchar p, guchar s, guchar d) { return (p ^ d); }
static guchar remmina_rop3_5b (guchar p, guchar s, guchar d) { return ((~((d | s)) | p) ^ d); }
static guchar remmina_rop3_5c (guchar p, guchar s, guchar d) { return (((d ^ s) | p) ^ d); }
static guchar remmina_rop3_5d (guchar p, guchar s, guchar d) { return ~(((~(s) | p) & d)); }
static guchar remmina_rop3_5e (guchar p, guchar s, guchar d) { return (((~(d) & s) | p) ^ d); }
static guchar remmina_rop3_5f (guchar p, guchar s, guchar d) { return ~((p & d)); }
static guchar remmina_rop3_60 (guchar p, guchar s, guchar d) { return ((s ^ d) & p); }
static guchar remmina_rop3_61 (guchar p, guchar s, guchar d) { return ~(((((s & d) | p) ^ s) ^ d)); }
static guchar remmina_rop3_62 (guchar p, guchar s, guchar d) { return (((d | p) & s) ^ d); }
static guchar remmina_rop3_63 (guchar p, guchar s, guchar d) { return ((~(p) | d) ^ s); }
static guchar remmina_rop3_64 (guchar p, guchar s, guchar d) { return (((s | p) & d) ^ s); }
static guchar remmina_rop3_65 (guchar p, guchar s, guchar d) { return ((~(p) | s) ^ d); }
static guchar remmina_rop3_66 (guchar p, guchar s, guchar d) { return (s ^ d); }
static guchar remmina_rop3_67 (guchar p, guchar s, guchar d) { return ((~((s | p)) | d) ^ s); }
static guchar remmina_rop3_68 (guchar p, guchar s, guchar d) { return ~((((~((s | d)) | p) ^ s) ^ d)); }
static guchar remmina_rop3_69 (guchar p, guchar s, guchar d) { return ~(((s ^ d) ^ p)); }
static guchar remmina_rop3_6a (guchar p, guchar s, guchar d) { return ((s & p) ^ d); }
static guchar remmina_rop3_6b (guchar p, guchar s, guchar d) { return ~(((((s | p) & d) ^ s) ^ p)); }
static guchar remmina_rop3_6c (guchar p, guchar s, guchar d) { return ((p & d) ^ s); }
static guchar remmina_rop3_6d (guchar p, guchar s, guchar d) { return ~(((((d | p) & s) ^ d) ^ p)); }
static guchar remmina_rop3_6e (guchar p, guchar s, guchar d) { return (((~(s) | p) & d) ^ s); }
static guchar remmina_rop3_6f (guchar p, guchar s, guchar d) { return ~((~((s ^ d)) & p)); }
static guchar remmina_rop3_70 (guchar p, guchar s, guchar d) { return (~((s & d)) & p); }
static guchar remmina_rop3_71 (guchar p, guchar s, guchar d) { return ~((((d ^ p) & (d ^ s)) ^ s)); }
static guchar remmina_rop3_72 (guchar p, guchar s, guchar d) { return (((s ^ p) | d) ^ s); }
static guchar remmina_rop3_73 (guchar p, guchar s, guchar d) { return ~(((~(p) | d) & s)); }
static guchar remmina_rop3_74 (guchar p, guchar s, guchar d) { return (((d ^ p) | s) ^ d); }
static guchar remmina_rop3_75 (guchar p, guchar s, guchar d) { return ~(((~(p) | s) & d)); }
static guchar remmina_rop3_76 (guchar p, guchar s, guchar d) { return (((~(s) & p) | d) ^ s); }
static guchar remmina_rop3_77 (guchar p, guchar s, guchar d) { return ~((s & d)); }
static guchar remmina_rop3_78 (guchar p, guchar s, guchar d) { return ((s & d) ^ p); }
static guchar remmina_rop3_79 (guchar p, guchar s, guchar d) { return ~(((((s | d) & p) ^ s) ^ d)); }
static guchar remmina_rop3_7a (guchar p, guchar s, guchar d) { return (((~(d) | s) & p) ^ d); }
static guchar remmina_rop3_7b (guchar p, guchar s, guchar d) { return ~((~((p ^ d)) & s)); }
static guchar remmina_rop3_7c (guchar p, guchar s, guchar d) { return (((~(s) | d) & p) ^ s); }
static guchar remmina_rop3_7d (guchar p, guchar s, guchar d) { return ~((~((s ^ p)) & d)); }
static guchar remmina_rop3_7e (guchar p, guchar s, guchar d) { return ((s ^ d) | (p ^ s)); }
static guchar remmina_rop3_7f (guchar p, guchar s, guchar d) { return ~(((s & p) & d)); }
static guchar remmina_rop3_80 (guchar p, guchar s, guchar d) { return ((s & p) & d); }
static guchar remmina_rop3_81 (guchar p, guchar s, guchar d) { return ~(((s ^ d) | (p ^ s))); }
static guchar remmina_rop3_82 (guchar p, guchar s, guchar d) { return (~((s ^ p)) & d); }
static guchar remmina_rop3_83 (guchar p, guchar s, guchar d) { return ~((((~(s) | d) & p) ^ s)); }
static guchar remmina_rop3_84 (guchar p, guchar s, guchar d) { return (~((p ^ d)) & s); }
static guchar remmina_rop3_85 (guchar p, guchar s, guchar d) { return ~((((~(p) | s) & d) ^ p)); }
static guchar remmina_rop3_86 (guchar p, guchar s, guchar d) { return ((((s | d) & p) ^ s) ^ d); }
static guchar remmina_rop3_87 (guchar p, guchar s, guchar d) { return ~(((s & d) ^ p)); }
static guchar remmina_rop3_88 (guchar p, guchar s, guchar d) { return (s & d); }
static guchar remmina_rop3_89 (guchar p, guchar s, guchar d) { return ~((((~(s) & p) | d) ^ s)); }
static guchar remmina_rop3_8a (guchar p, guchar s, guchar d) { return ((~(p) | s) & d); }
static guchar remmina_rop3_8b (guchar p, guchar s, guchar d) { return ~((((d ^ p) | s) ^ d)); }
static guchar remmina_rop3_8c (guchar p, guchar s, guchar d) { return ((~(p) | d) & s); }
static guchar remmina_rop3_8d (guchar p, guchar s, guchar d) { return ~((((s ^ p) | d) ^ s)); }
static guchar remmina_rop3_8e (guchar p, guchar s, guchar d) { return (((d ^ p) & (d ^ s)) ^ s); }
static guchar remmina_rop3_8f (guchar p, guchar s, guchar d) { return ~((~((s & d)) & p)); }
static guchar remmina_rop3_90 (guchar p, guchar s, guchar d) { return (~((s ^ d)) & p); }
static guchar remmina_rop3_91 (guchar p, guchar s, guchar d) { return ~((((~(s) | p) & d) ^ s)); }
static guchar remmina_rop3_92 (guchar p, guchar s, guchar d) { return ((((p | d) & s) ^ p) ^ d); }
static guchar remmina_rop3_93 (guchar p, guchar s, guchar d) { return ~(((d & p) ^ s)); }
static guchar remmina_rop3_94 (guchar p, guchar s, guchar d) { return ((((s | p) & d) ^ s) ^ p); }
static guchar remmina_rop3_95 (guchar p, guchar s, guchar d) { return ~(((s & p) ^ d)); }
static guchar remmina_rop3_96 (guchar p, guchar s, guchar d) { return ((s ^ p) ^ d); }
static guchar remmina_rop3_97 (guchar p, guchar s, guchar d) { return (((~((s | p)) | d) ^ s) ^ p); }
static guchar remmina_rop3_98 (guchar p, guchar s, guchar d) { return ~(((~((s | p)) | d) ^ s)); }
static guchar remmina_rop3_99 (guchar p, guchar s, guchar d) { return ~((s ^ d)); }
static guchar remmina_rop3_9a (guchar p, guchar s, guchar d) { return ((~(s) & p) ^ d); }
static guchar remmina_rop3_9b (guchar p, guchar s, guchar d) { return ~((((s | p) & d) ^ s)); }
static guchar remmina_rop3_9c (guchar p, guchar s, guchar d) { return ((~(d) & p) ^ s); }
static guchar remmina_rop3_9d (guchar p, guchar s, guchar d) { return ~((((d | p) & s) ^ d)); }
static guchar remmina_rop3_9e (guchar p, guchar s, guchar d) { return ((((s & d) | p) ^ s) ^ d); }
static guchar remmina_rop3_9f (guchar p, guchar s, guchar d) { return ~(((s ^ d) & p)); }
static guchar remmina_rop3_a0 (guchar p, guchar s, guchar d) { return (p & d); }
static guchar remmina_rop3_a1 (guchar p, guchar s, guchar d) { return ~((((~(p) & s) | d) ^ p)); }
static guchar remmina_rop3_a2 (guchar p, guchar s, guchar d) { return ((~(s) | p) & d); }
static guchar remmina_rop3_a3 (guchar p, guchar s, guchar d) { return ~((((d ^ s) | p) ^ d)); }
static guchar remmina_rop3_a4 (guchar p, guchar s, guchar d) { return ~(((~((p | s)) | d) ^ p)); }
static guchar remmina_rop3_a5 (guchar p, guchar s, guchar d) { return ~((d ^ p)); }
static guchar remmina_rop3_a6 (guchar p, guchar s, guchar d) { return ((~(p) & s) ^ d); }
static guchar remmina_rop3_a7 (guchar p, guchar s, guchar d) { return ~((((p | s) & d) ^ p)); }
static guchar remmina_rop3_a8 (guchar p, guchar s, guchar d) { return ((s | p) & d); }
static guchar remmina_rop3_a9 (guchar p, guchar s, guchar d) { return ~(((s | p) ^ d)); }
static guchar remmina_rop3_aa (guchar p, guchar s, guchar d) { return d; }
static guchar remmina_rop3_ab (guchar p, guchar s, guchar d) { return (~((s | p)) | d); }
static guchar remmina_rop3_ac (guchar p, guchar s, guchar d) { return (((s ^ d) & p) ^ s); }
static guchar remmina_rop3_ad (guchar p, guchar s, guchar d) { return ~((((d & s) | p) ^ d)); }
static guchar remmina_rop3_ae (guchar p, guchar s, guchar d) { return ((~(p) & s) | d); }
static guchar remmina_rop3_af (guchar p, guchar s, guchar d) { return (~(p) | d); }
static guchar remmina_rop3_b0 (guchar p, guchar s, guchar d) { return ((~(s) | d) & p); }
static guchar remmina_rop3_b1 (guchar p, guchar s, guchar d) { return ~((((p ^ s) | d) ^ p)); }
static guchar remmina_rop3_b2 (guchar p, guchar s, guchar d) { return (((s ^ d) | (p ^ s)) ^ s); }
static guchar remmina_rop3_b3 (guchar p, guchar s, guchar d) { return ~((~((p & d)) & s)); }
static guchar remmina_rop3_b4 (guchar p, guchar s, guchar d) { return ((~(d) & s) ^ p); }
static guchar remmina_rop3_b5 (guchar p, guchar s, guchar d) { return ~((((d | s) & p) ^ d)); }
static guchar remmina_rop3_b6 (guchar p, guchar s, guchar d) { return ((((p & d) | s) ^ p) ^ d); }
static guchar remmina_rop3_b7 (guchar p, guchar s, guchar d) { return ~(((p ^ d) & s)); }
static guchar remmina_rop3_b8 (guchar p, guchar s, guchar d) { return (((p ^ d) & s) ^ p); }
static guchar remmina_rop3_b9 (guchar p, guchar s, guchar d) { return ~((((d & p) | s) ^ d)); }
static guchar remmina_rop3_ba (guchar p, guchar s, guchar d) { return ((~(s) & p) | d); }
static guchar remmina_rop3_bb (guchar p, guchar s, guchar d) { return (~(s) | d); }
static guchar remmina_rop3_bc (guchar p, guchar s, guchar d) { return ((~((s & d)) & p) ^ s); }
static guchar remmina_rop3_bd (guchar p, guchar s, guchar d) { return ~(((d ^ p) & (d ^ s))); }
static guchar remmina_rop3_be (guchar p, guchar s, guchar d) { return ((s ^ p) | d); }
static guchar remmina_rop3_bf (guchar p, guchar s, guchar d) { return (~((s & p)) | d); }
static guchar remmina_rop3_c0 (guchar p, guchar s, guchar d) { return (s & p); }
static guchar remmina_rop3_c1 (guchar p, guchar s, guchar d) { return ~((((~(s) & d) | p) ^ s)); }
static guchar remmina_rop3_c2 (guchar p, guchar s, guchar d) { return ~(((~((s | d)) | p) ^ s)); }
static guchar remmina_rop3_c3 (guchar p, guchar s, guchar d) { return ~((s ^ p)); }
static guchar remmina_rop3_c4 (guchar p, guchar s, guchar d) { return ((~(d) | p) & s); }
static guchar remmina_rop3_c5 (guchar p, guchar s, guchar d) { return ~((((s ^ d) | p) ^ s)); }
static guchar remmina_rop3_c6 (guchar p, guchar s, guchar d) { return ((~(p) & d) ^ s); }
static guchar remmina_rop3_c7 (guchar p, guchar s, guchar d) { return ~((((p | d) & s) ^ p)); }
static guchar remmina_rop3_c8 (guchar p, guchar s, guchar d) { return ((p | d) & s); }
static guchar remmina_rop3_c9 (guchar p, guchar s, guchar d) { return ~(((d | p) ^ s)); }
static guchar remmina_rop3_ca (guchar p, guchar s, guchar d) { return (((d ^ s) & p) ^ d); }
static guchar remmina_rop3_cb (guchar p, guchar s, guchar d) { return ~((((s & d) | p) ^ s)); }
static guchar remmina_rop3_cc (guchar p, guchar s, guchar d) { return s; }
static guchar remmina_rop3_cd (guchar p, guchar s, guchar d) { return (~((p | d)) | s); }
static guchar remmina_rop3_ce (guchar p, guchar s, guchar d) { return ((~(p) & d) | s); }
static guchar remmina_rop3_cf (guchar p, guchar s, guchar d) { return (~(p) | s); }
static guchar remmina_rop3_d0 (guchar p, guchar s, guchar d) { return ((~(d) | s) & p); }
static guchar remmina_rop3_d1 (guchar p, guchar s, guchar d) { return ~((((p ^ d) | s) ^ p)); }
static guchar remmina_rop3_d2 (guchar p, guchar s, guchar d) { return ((~(s) & d) ^ p); }
static guchar remmina_rop3_d3 (guchar p, guchar s, guchar d) { return ~((((s | d) & p) ^ s)); }
static guchar remmina_rop3_d4 (guchar p, guchar s, guchar d) { return (((d ^ p) & (p ^ s)) ^ s); }
static guchar remmina_rop3_d5 (guchar p, guchar s, guchar d) { return ~((~((s & p)) & d)); }
static guchar remmina_rop3_d6 (guchar p, guchar s, guchar d) { return ((((s & p) | d) ^ s) ^ p); }
static guchar remmina_rop3_d7 (guchar p, guchar s, guchar d) { return ~(((s ^ p) & d)); }
static guchar remmina_rop3_d8 (guchar p, guchar s, guchar d) { return (((p ^ s) & d) ^ p); }
static guchar remmina_rop3_d9 (guchar p, guchar s, guchar d) { return ~((((s & p) | d) ^ s)); }
static guchar remmina_rop3_da (guchar p, guchar s, guchar d) { return ((~((d & s)) & p) ^ d); }
static guchar remmina_rop3_db (guchar p, guchar s, guchar d) { return ~(((s ^ d) & (p ^ s))); }
static guchar remmina_rop3_dc (guchar p, guchar s, guchar d) { return ((~(d) & p) | s); }
static guchar remmina_rop3_dd (guchar p, guchar s, guchar d) { return (~(d) | s); }
static guchar remmina_rop3_de (guchar p, guchar s, guchar d) { return ((p ^ d) | s); }
static guchar remmina_rop3_df (guchar p, guchar s, guchar d) { return (~((p & d)) | s); }
static guchar remmina_rop3_e0 (guchar p, guchar s, guchar d) { return ((s | d) & p); }
static guchar remmina_rop3_e1 (guchar p, guchar s, guchar d) { return ~(((s | d) ^ p)); }
static guchar remmina_rop3_e2 (guchar p, guchar s, guchar d) { return (((d ^ p) & s) ^ d); }
static guchar remmina_rop3_e3 (guchar p, guchar s, guchar d) { return ~((((p & d) | s) ^ p)); }
static guchar remmina_rop3_e4 (guchar p, guchar s, guchar d) { return (((s ^ p) & d) ^ s); }
static guchar remmina_rop3_e5 (guchar p, guchar s, guchar d) { return ~((((p & s) | d) ^ p)); }
static guchar remmina_rop3_e6 (guchar p, guchar s, guchar d) { return ((~((s & p)) & d) ^ s); }
static guchar remmina_rop3_e7 (guchar p, guchar s, guchar d) { return ~(((d ^ p) & (p ^ s))); }
static guchar remmina_rop3_e8 (guchar p, guchar s, guchar d) { return (((s ^ d) & (p ^ s)) ^ s); }
static guchar remmina_rop3_e9 (guchar p, guchar s, guchar d) { return ~((((~((s & d)) & p) ^ s) ^ d)); }
static guchar remmina_rop3_ea (guchar p, guchar s, guchar d) { return ((s & p) | d); }
static guchar remmina_rop3_eb (guchar p, guchar s, guchar d) { return (~((s ^ p)) | d); }
static guchar remmina_rop3_ec (guchar p, guchar s, guchar d) { return ((p & d) | s); }
static guchar remmina_rop3_ed (guchar p, guchar s, guchar d) { return (~((p ^ d)) | s); }
static guchar remmina_rop3_ee (guchar p, guchar s, guchar d) { return (s | d); }
static guchar remmina_rop3_ef (guchar p, guchar s, guchar d) { return ((~(p) | d) | s); }
static guchar remmina_rop3_f0 (guchar p, guchar s, guchar d) { return p; }
static guchar remmina_rop3_f1 (guchar p, guchar s, guchar d) { return (~((s | d)) | p); }
static guchar remmina_rop3_f2 (guchar p, guchar s, guchar d) { return ((~(s) & d) | p); }
static guchar remmina_rop3_f3 (guchar p, guchar s, guchar d) { return (~(s) | p); }
static guchar remmina_rop3_f4 (guchar p, guchar s, guchar d) { return ((~(d) & s) | p); }
static guchar remmina_rop3_f5 (guchar p, guchar s, guchar d) { return (~(d) | p); }
static guchar remmina_rop3_f6 (guchar p, guchar s, guchar d) { return ((s ^ d) | p); }
static guchar remmina_rop3_f7 (guchar p, guchar s, guchar d) { return (~((s & d)) | p); }
static guchar remmina_rop3_f8 (guchar p, guchar s, guchar d) { return ((s & d) | p); }
static guchar remmina_rop3_f9 (guchar p, guchar s, guchar d) { return (~((s ^ d)) | p); }
static guchar remmina_rop3_fa (guchar p, guchar s, guchar d) { return (p | d); }
static guchar remmina_rop3_fb (guchar p, guchar s, guchar d) { return ((~(s) | p) | d); }
static guchar remmina_rop3_fc (guchar p, guchar s, guchar d) { return (s | p); }
static guchar remmina_rop3_fd (guchar p, guchar s, guchar d) { return ((~(d) | s) | p); }
static guchar remmina_rop3_fe (guchar p, guchar s, guchar d) { return ((s | p) | d); }
static guchar remmina_rop3_ff (guchar p, guchar s, guchar d) { return 0xff; }

static RemminaROP3Func remmina_rop3_func[] = {
    remmina_rop3_00,
    remmina_rop3_01,
    remmina_rop3_02,
    remmina_rop3_03,
    remmina_rop3_04,
    remmina_rop3_05,
    remmina_rop3_06,
    remmina_rop3_07,
    remmina_rop3_08,
    remmina_rop3_09,
    remmina_rop3_0a,
    remmina_rop3_0b,
    remmina_rop3_0c,
    remmina_rop3_0d,
    remmina_rop3_0e,
    remmina_rop3_0f,
    remmina_rop3_10,
    remmina_rop3_11,
    remmina_rop3_12,
    remmina_rop3_13,
    remmina_rop3_14,
    remmina_rop3_15,
    remmina_rop3_16,
    remmina_rop3_17,
    remmina_rop3_18,
    remmina_rop3_19,
    remmina_rop3_1a,
    remmina_rop3_1b,
    remmina_rop3_1c,
    remmina_rop3_1d,
    remmina_rop3_1e,
    remmina_rop3_1f,
    remmina_rop3_20,
    remmina_rop3_21,
    remmina_rop3_22,
    remmina_rop3_23,
    remmina_rop3_24,
    remmina_rop3_25,
    remmina_rop3_26,
    remmina_rop3_27,
    remmina_rop3_28,
    remmina_rop3_29,
    remmina_rop3_2a,
    remmina_rop3_2b,
    remmina_rop3_2c,
    remmina_rop3_2d,
    remmina_rop3_2e,
    remmina_rop3_2f,
    remmina_rop3_30,
    remmina_rop3_31,
    remmina_rop3_32,
    remmina_rop3_33,
    remmina_rop3_34,
    remmina_rop3_35,
    remmina_rop3_36,
    remmina_rop3_37,
    remmina_rop3_38,
    remmina_rop3_39,
    remmina_rop3_3a,
    remmina_rop3_3b,
    remmina_rop3_3c,
    remmina_rop3_3d,
    remmina_rop3_3e,
    remmina_rop3_3f,
    remmina_rop3_40,
    remmina_rop3_41,
    remmina_rop3_42,
    remmina_rop3_43,
    remmina_rop3_44,
    remmina_rop3_45,
    remmina_rop3_46,
    remmina_rop3_47,
    remmina_rop3_48,
    remmina_rop3_49,
    remmina_rop3_4a,
    remmina_rop3_4b,
    remmina_rop3_4c,
    remmina_rop3_4d,
    remmina_rop3_4e,
    remmina_rop3_4f,
    remmina_rop3_50,
    remmina_rop3_51,
    remmina_rop3_52,
    remmina_rop3_53,
    remmina_rop3_54,
    remmina_rop3_55,
    remmina_rop3_56,
    remmina_rop3_57,
    remmina_rop3_58,
    remmina_rop3_59,
    remmina_rop3_5a,
    remmina_rop3_5b,
    remmina_rop3_5c,
    remmina_rop3_5d,
    remmina_rop3_5e,
    remmina_rop3_5f,
    remmina_rop3_60,
    remmina_rop3_61,
    remmina_rop3_62,
    remmina_rop3_63,
    remmina_rop3_64,
    remmina_rop3_65,
    remmina_rop3_66,
    remmina_rop3_67,
    remmina_rop3_68,
    remmina_rop3_69,
    remmina_rop3_6a,
    remmina_rop3_6b,
    remmina_rop3_6c,
    remmina_rop3_6d,
    remmina_rop3_6e,
    remmina_rop3_6f,
    remmina_rop3_70,
    remmina_rop3_71,
    remmina_rop3_72,
    remmina_rop3_73,
    remmina_rop3_74,
    remmina_rop3_75,
    remmina_rop3_76,
    remmina_rop3_77,
    remmina_rop3_78,
    remmina_rop3_79,
    remmina_rop3_7a,
    remmina_rop3_7b,
    remmina_rop3_7c,
    remmina_rop3_7d,
    remmina_rop3_7e,
    remmina_rop3_7f,
    remmina_rop3_80,
    remmina_rop3_81,
    remmina_rop3_82,
    remmina_rop3_83,
    remmina_rop3_84,
    remmina_rop3_85,
    remmina_rop3_86,
    remmina_rop3_87,
    remmina_rop3_88,
    remmina_rop3_89,
    remmina_rop3_8a,
    remmina_rop3_8b,
    remmina_rop3_8c,
    remmina_rop3_8d,
    remmina_rop3_8e,
    remmina_rop3_8f,
    remmina_rop3_90,
    remmina_rop3_91,
    remmina_rop3_92,
    remmina_rop3_93,
    remmina_rop3_94,
    remmina_rop3_95,
    remmina_rop3_96,
    remmina_rop3_97,
    remmina_rop3_98,
    remmina_rop3_99,
    remmina_rop3_9a,
    remmina_rop3_9b,
    remmina_rop3_9c,
    remmina_rop3_9d,
    remmina_rop3_9e,
    remmina_rop3_9f,
    remmina_rop3_a0,
    remmina_rop3_a1,
    remmina_rop3_a2,
    remmina_rop3_a3,
    remmina_rop3_a4,
    remmina_rop3_a5,
    remmina_rop3_a6,
    remmina_rop3_a7,
    remmina_rop3_a8,
    remmina_rop3_a9,
    remmina_rop3_aa,
    remmina_rop3_ab,
    remmina_rop3_ac,
    remmina_rop3_ad,
    remmina_rop3_ae,
    remmina_rop3_af,
    remmina_rop3_b0,
    remmina_rop3_b1,
    remmina_rop3_b2,
    remmina_rop3_b3,
    remmina_rop3_b4,
    remmina_rop3_b5,
    remmina_rop3_b6,
    remmina_rop3_b7,
    remmina_rop3_b8,
    remmina_rop3_b9,
    remmina_rop3_ba,
    remmina_rop3_bb,
    remmina_rop3_bc,
    remmina_rop3_bd,
    remmina_rop3_be,
    remmina_rop3_bf,
    remmina_rop3_c0,
    remmina_rop3_c1,
    remmina_rop3_c2,
    remmina_rop3_c3,
    remmina_rop3_c4,
    remmina_rop3_c5,
    remmina_rop3_c6,
    remmina_rop3_c7,
    remmina_rop3_c8,
    remmina_rop3_c9,
    remmina_rop3_ca,
    remmina_rop3_cb,
    remmina_rop3_cc,
    remmina_rop3_cd,
    remmina_rop3_ce,
    remmina_rop3_cf,
    remmina_rop3_d0,
    remmina_rop3_d1,
    remmina_rop3_d2,
    remmina_rop3_d3,
    remmina_rop3_d4,
    remmina_rop3_d5,
    remmina_rop3_d6,
    remmina_rop3_d7,
    remmina_rop3_d8,
    remmina_rop3_d9,
    remmina_rop3_da,
    remmina_rop3_db,
    remmina_rop3_dc,
    remmina_rop3_dd,
    remmina_rop3_de,
    remmina_rop3_df,
    remmina_rop3_e0,
    remmina_rop3_e1,
    remmina_rop3_e2,
    remmina_rop3_e3,
    remmina_rop3_e4,
    remmina_rop3_e5,
    remmina_rop3_e6,
    remmina_rop3_e7,
    remmina_rop3_e8,
    remmina_rop3_e9,
    remmina_rop3_ea,
    remmina_rop3_eb,
    remmina_rop3_ec,
    remmina_rop3_ed,
    remmina_rop3_ee,
    remmina_rop3_ef,
    remmina_rop3_f0,
    remmina_rop3_f1,
    remmina_rop3_f2,
    remmina_rop3_f3,
    remmina_rop3_f4,
    remmina_rop3_f5,
    remmina_rop3_f6,
    remmina_rop3_f7,
    remmina_rop3_f8,
    remmina_rop3_f9,
    remmina_rop3_fa,
    remmina_rop3_fb,
    remmina_rop3_fc,
    remmina_rop3_fd,
    remmina_rop3_fe,
    remmina_rop3_ff,
    NULL
};
/* --------------------------------------------------------------------- */

typedef struct _RemminaGlyph
{
    gint width;
    gint height;
    gint rowstride;
    guchar *data;
} RemminaGlyph;

#define GLYPH_PIXEL(_rowdata,_x) (_rowdata[(_x) / 8] & (0x80 >> ((_x) % 8)))

static guchar hatch_patterns[] = {
    0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, /* 0 - bsHorizontal */
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, /* 1 - bsVertical */
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, /* 2 - bsFDiagonal */
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, /* 3 - bsBDiagonal */
    0x08, 0x08, 0x08, 0xff, 0x08, 0x08, 0x08, 0x08, /* 4 - bsCross */
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81  /* 5 - bsDiagCross */
};

static void
remmina_plugin_rdpui_color_convert (RemminaPluginRdpData *gpdata,
    gint cv, guchar pixel[3])
{
    switch (gpdata->settings->server_depth)
    {
    case 24:
        pixel[0] = (cv & 0xff);
        pixel[1] = ((cv & 0xff00) >> 8);
        pixel[2] = ((cv & 0xff0000) >> 16);
        break;
    case 16:
        pixel[0] = ((cv & 0xf800) >> 8) | ((cv & 0xe000) >> 13);
        pixel[1] = ((cv & 0x07e0) >> 3) | ((cv & 0x0600) >> 9);
        pixel[2] = ((cv & 0x1f) << 3) | ((cv & 0x1c) >> 2);
        break;
    case 15:
        pixel[0] = ((cv & 0x7c00) >> 7) | ((cv & 0x7000) >> 12);
        pixel[1] = ((cv & 0x03e0) >> 2) | ((cv & 0x0380) >> 7);
        pixel[2] = ((cv & 0x1f) << 3) | ((cv & 0x1c) >> 2);
        break;
    case 8:
        if (gpdata->colormap)
        {
            memcpy (pixel, gpdata->colormap + (cv & 0xff) * 3, 3);
        }
        break;
    }
}

static void
remmina_plugin_rdpui_bitmap_flip (GdkPixbuf *pixbuf)
{
    guchar *data;
    guchar *buf;
    gint rowstride;
    gint width;
    gint height;
    gint iy;
    gint cy;

    data = gdk_pixbuf_get_pixels (pixbuf);
    width = gdk_pixbuf_get_width (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    buf = (guchar *) malloc (rowstride);
    cy = height / 2;
    for (iy = 0; iy < cy; iy++)
    {
        memcpy (buf, data + iy * rowstride, rowstride);
        memcpy (data + iy * rowstride, data + (height - iy - 1) * rowstride, rowstride);
        memcpy (data + (height - iy - 1) * rowstride, buf, rowstride);
    }
    free (buf);
}

static GdkPixbuf*
remmina_plugin_rdpui_bitmap_convert (RemminaPluginRdpData *gpdata,
    gint width, gint height, gint bpp, gboolean alpha, guchar *in_data)
{
    GdkPixbuf *pixbuf;
    guchar *out_data;
    gint ix;
    gint iy;
    gint rowstride;
    guchar *src;
    guchar *dst;

    if (bpp == 0)
    {
        bpp = gpdata->settings->server_depth;
    }
    pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, alpha, 8, width, height);
    out_data = gdk_pixbuf_get_pixels (pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    switch (bpp)
    {
    case 32:
        src = in_data;
        for (iy = 0; iy < height; iy++)
        {
            dst = out_data + iy * rowstride;
            for (ix = 0; ix < width; ix++)
            {
                *dst++ = *(src + 2);
                *dst++ = *(src + 1);
                *dst++ = *src;
                if (alpha) *dst++ = 0xff;
                src += 4;
            }
        }
        break;

    case 24:
        src = in_data;
        for (iy = 0; iy < height; iy++)
        {
            dst = out_data + iy * rowstride;
            for (ix = 0; ix < width; ix++)
            {
                *dst++ = *(src + 2);
                *dst++ = *(src + 1);
                *dst++ = *src;
                if (alpha) *dst++ = 0xff;
                src += 3;
            }
        }
        break;

    case 16:
        src = in_data;
        for (iy = 0; iy < height; iy++)
        {
            dst = out_data + iy * rowstride;
            for (ix = 0; ix < width; ix++)
            {
                *dst++ = (*(src + 1) & 0xf8) | ((*(src + 1) & 0xe0) >> 5);
                *dst++ = ((*(src + 1) & 0x07) << 5) | ((*src & 0xe0) >> 3) | ((*(src + 1) & 0x06) >> 1);
                *dst++ = ((*src & 0x1f) << 3) | ((*src & 0x1c) >> 2);
                if (alpha) *dst++ = 0xff;
                src += 2;
            }
        }
        break;

    case 15:
        src = in_data;
        for (iy = 0; iy < height; iy++)
        {
            dst = out_data + iy * rowstride;
            for (ix = 0; ix < width; ix++)
            {
                *dst++ = ((*(src + 1) & 0x7c) << 1) | ((*(src + 1) & 0x70) >> 4);
                *dst++ = ((*(src + 1) & 0x03) << 6) | ((*src & 0xe0) >> 2) | (*(src + 1) & 0x03);
                *dst++ = ((*src & 0x1f) << 3) | ((*src & 0x1c) >> 2);
                if (alpha) *dst++ = 0xff;
                src += 2;
            }
        }
        break;

    case 8:
        src = in_data;
        for (iy = 0; iy < height; iy++)
        {
            dst = out_data + iy * rowstride;
            for (ix = 0; ix < width; ix++)
            {
                memcpy (dst, gpdata->colormap + (*src++) * 3, 3);
                dst += 3;
                if (alpha) *dst++ = 0xff;
            }
        }
        break;

    case 1:
        for (iy = 0; iy < height; iy++)
        {
            dst = out_data + iy * rowstride;
            src = in_data + (iy * ((width + 7) / 8));
            for (ix = 0; ix < width; ix++)
            {
                memset (dst, (GLYPH_PIXEL (src, ix) ? 0xff : 0), 3);
                dst += 3;
                if (alpha) *dst++ = 0xff;
            }
        }
        break;
    }
    return pixbuf;
}

static void
remmina_plugin_rdpui_bitmap_apply_mask (GdkPixbuf *pixbuf, guchar *mask)
{
    guchar *data;
    gint width;
    gint height;
    gint ix;
    gint iy;
    gint rowstride;
    guchar *src;
    guchar *dst;

    data = gdk_pixbuf_get_pixels (pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    width = gdk_pixbuf_get_width (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    for (iy = 0; iy < height; iy++)
    {
        dst = data + iy * rowstride;
        src = mask + (iy * ((width + 7) / 8));
        for (ix = 0; ix < width; ix++)
        {
            if (GLYPH_PIXEL (src, ix))
            {
                *(dst + 3) = (*dst + *(dst + 1) + *(dst + 2)) / 3;
                *dst = ~(*dst);
                *(dst + 1) = ~(*(dst + 1));
                *(dst + 2) = ~(*(dst + 2));
            }
            else
            {
                *(dst + 3) = 0xff;
            }
            dst += 4;
        }
    }
}

static void
remmina_plugin_rdpui_process_clip_full (gint *x, gint *y, gint *w, gint *h, gint *srcx, gint *srcy,
    gint clip_x, gint clip_y, gint clip_w, gint clip_h)
{
    if (*x < clip_x)
    {
        *w -= clip_x - *x;
        if (srcx) *srcx += clip_x - *x;
        *x = clip_x;
    }
    *w = MAX(0, MIN (*w, clip_w));
    if (*y < clip_y)
    {
        *h -= clip_y - *y;
        if (srcy) *srcy += clip_y - *y;
        *y = clip_y;
    }
    *h = MAX(0, MIN (*h, clip_h));
    if (*w == 0 || *h == 0) return;

    if (*x + *w > clip_x + clip_w)
    {
        *w -= *x + *w - (clip_x + clip_w);
        *w = MAX (0, *w);
    }
    if (*y + *h > clip_y + clip_h)
    {
        *h -= *y + *h - (clip_y + clip_h);
        *h = MAX (0, *h);
    }
}

static void
remmina_plugin_rdpui_process_clip (RemminaPluginRdpData *gpdata,
    gint *x, gint *y, gint *w, gint *h, gint *srcx, gint *srcy)
{
    if (gpdata->clip)
    {
        remmina_plugin_rdpui_process_clip_full (x, y, w, h, srcx, srcy,
            gpdata->clip_x, gpdata->clip_y, gpdata->clip_w, gpdata->clip_h);
    }
}

static void
remmina_plugin_rdpui_process_rop3 (RemminaPluginRdpData *gpdata, guchar opcode,
    gint x, gint y, gint cx, gint cy, GdkPixbuf *src, gint srcx, gint srcy)
{
    GdkPixbuf *dst;
    guchar *srcbuf;
    guchar *dstbuf;
    guchar *srcbufbase;
    guchar *dstbufbase;
    gint srcbufrs;
    gint dstbufrs;
    gint ix, iy;
    guchar p;
    gint p_rowstride;
    gint d_rowstride;

    remmina_plugin_rdpui_process_clip (gpdata, &x, &y, &cx, &cy, &srcx, &srcy);
    if (src)
    {
        cx = MIN (cx, gdk_pixbuf_get_width (src) - srcx);
        cy = MIN (cy, gdk_pixbuf_get_height (src) - srcy);
    }
    cx = MIN (cx, gdk_pixbuf_get_width (gpdata->drw_buffer) - x);
    cy = MIN (cy, gdk_pixbuf_get_height (gpdata->drw_buffer) - y);
    if (cx <= 0 || cy <= 0) return;
    dst = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, cx, cy);
    gdk_pixbuf_copy_area (gpdata->drw_buffer, x, y, cx, cy, dst, 0, 0);
    p_rowstride = gpdata->pattern_w * 3;
    d_rowstride = cx * 3;

    srcbufrs = (src ? gdk_pixbuf_get_rowstride (src) : 0);
    srcbufbase = (src ? gdk_pixbuf_get_pixels (src) + srcy * srcbufrs + srcx * 3 : NULL);
    dstbufrs = gdk_pixbuf_get_rowstride (dst);
    dstbufbase = gdk_pixbuf_get_pixels (dst);
    for (iy = 0; iy < cy; iy++)
    {
        dstbuf = dstbufbase;
        dstbufbase += dstbufrs;
        srcbuf = srcbufbase;
        srcbufbase += srcbufrs;
        /* The simplest rop3 that can be done in row batch */
        switch (opcode)
        {
        case 0xcc:
            if (srcbuf) memcpy (dstbuf, srcbuf, d_rowstride);
            continue;
        case 0x00:
        case 0xff:
            memset (dstbuf, opcode, d_rowstride);
            continue;
        case 0xaa:
            continue;
        }
        for (ix = 0; ix < d_rowstride; ix++)
        {
            if (p_rowstride > 0)
            {
                p = gpdata->pattern[(iy % gpdata->pattern_h) * p_rowstride +
                    (ix % p_rowstride)];
            }
            else
            {
                p = 0;
            }
            *dstbuf = (*(remmina_rop3_func[opcode])) (p, (srcbuf ? *srcbuf++ : 0), *dstbuf);
            dstbuf++;
        }
    }
    gdk_pixbuf_copy_area (dst, 0, 0, cx, cy, gpdata->drw_buffer, x, y);
    g_object_unref (dst);
}

static guchar
remmina_plugin_rdpui_calc_rop2 (guchar p, guchar d, guchar opcode)
{
    gint i;
    gint val;
    guchar r;

    r = 0;
    for (i = 0; i < 8; i++)
    {
        val = (((p >> i) & 1) << 1) | ((d >> i) & 1);
        r |= (((opcode >> val) & 1) ? (1 << i) : 0);
    }
    return r;
}

static void
remmina_plugin_rdpui_process_rop2 (RemminaPluginRdpData *gpdata, guchar opcode,
    gint x, gint y, gint cx, gint cy)
{
    GdkPixbuf *dst;
    guchar *dstbuf;
    gint ix, iy;
    guchar p;
    gint p_rowstride;

    remmina_plugin_rdpui_process_clip (gpdata, &x, &y, &cx, &cy, NULL, NULL);
    dst = gpdata->drw_buffer;
    cx = MIN (cx, gdk_pixbuf_get_width (dst) - x);
    cy = MIN (cy, gdk_pixbuf_get_height (dst) - y);
    if (cx <= 0 || cy <= 0) return;
    p_rowstride = gpdata->pattern_w * 3;

    for (iy = 0; iy < cy; iy++)
    {
        dstbuf = gdk_pixbuf_get_pixels (dst) + (iy + y) * gdk_pixbuf_get_rowstride (dst) + x * 3;
        for (ix = 0; ix < cx * 3; ix++)
        {
            if (p_rowstride > 0)
            {
                p = gpdata->pattern[(iy % gpdata->pattern_h) * p_rowstride +
                    (ix % p_rowstride)];
            }
            else
            {
                p = 0;
            }
            *dstbuf = remmina_plugin_rdpui_calc_rop2 (p, *dstbuf, opcode);
            dstbuf++;
        }
    }
}

static void
remmina_plugin_rdpui_fill_pattern (RemminaPluginRdpData *gpdata,
    guchar *pat, gint reverse)
{
    guchar *dstpat;
    guchar *srcpat;
    gint ix, iy;

    gpdata->pattern_w = 8;
    gpdata->pattern_h = 8;
    dstpat = gpdata->pattern;
    srcpat = (reverse ? pat + 7 : pat);
    for (iy = 0; iy < 8; iy++)
    {
        for (ix = 0; ix < 8; ix++)
        {
            memcpy (dstpat, ((*srcpat & (0x80 >> ix)) ? gpdata->bgcolor : gpdata->fgcolor), 3);
            dstpat += 3;
        }
        if (reverse)
        {
            srcpat--;
        }
        else
        {
            srcpat++;
        }
    }
}

static void
remmina_plugin_rdpui_patline (RemminaPluginRdpData *gpdata,
    gint opcode, gint x0, gint y0, gint x1, gint y1)
{
    gint dx, dy;
    gint sx, sy;
    gint dx2, dy2;
    gint e;
    gint i;

    dx = x1 - x0;
    if (dx >= 0)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
        dx = -dx;
    }
    dy = y1 - y0;
    if (dy >= 0)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
        dy = -dy;
    }
    dx2 = dx << 1;
    dy2 = dy << 1;
    if (dx > dy)
    {
        e = dy2 - dx;
        for (i = 0; i < dx; i++)
        {
            remmina_plugin_rdpui_process_rop2 (gpdata, opcode, x0, y0, 1, 1);
            if (e >= 0)
            {
                e -= dx2;
                y0 += sy;
            }
            e += dy2;
            x0 += sx;
        }
    }
    else
    {
        e = dx2 - dy;
        for (i = 0; i < dy; i++)
        {
            remmina_plugin_rdpui_process_rop2 (gpdata, opcode, x0, y0, 1, 1);
            if (e >= 0)
            {
                e -= dy2;
                x0 += sx;
            }
            e += dx2;
            y0 += sy;
        }
    }
}

static void
remmina_plugin_rdpui_queuedraw (RemminaProtocolWidget *gp, gint x, gint y, gint w, gint h)
{
    RemminaPluginRdpData *gpdata;
    gint nx2, ny2, ox2, oy2;

    gpdata = GET_DATA (gp);

    if (gpdata->queuedraw_handler)
    {
        nx2 = x + w;
        ny2 = y + h;
        ox2 = gpdata->queuedraw_x + gpdata->queuedraw_w;
        oy2 = gpdata->queuedraw_y + gpdata->queuedraw_h;
        gpdata->queuedraw_x = MIN (gpdata->queuedraw_x, x);
        gpdata->queuedraw_y = MIN (gpdata->queuedraw_y, y);
        gpdata->queuedraw_w = MAX (ox2, nx2) - gpdata->queuedraw_x;
        gpdata->queuedraw_h = MAX (oy2, ny2) - gpdata->queuedraw_y;
    }
    else
    {
        gpdata->queuedraw_x = x;
        gpdata->queuedraw_y = y;
        gpdata->queuedraw_w = w;
        gpdata->queuedraw_h = h;
        gpdata->queuedraw_handler = IDLE_ADD ((GSourceFunc) remmina_plugin_rdpev_queuedraw, gp);
    }
}

static void
remmina_plugin_rdpui_queuecursor (RemminaProtocolWidget *gp, GdkPixbuf *pixbuf, gboolean null_cursor, gint x, gint y)
{
    RemminaPluginRdpData *gpdata;

    gpdata = GET_DATA (gp);

    gpdata->queuecursor_pixbuf = pixbuf;
    gpdata->queuecursor_null = null_cursor;
    gpdata->queuecursor_x = x;
    gpdata->queuecursor_y = y;
    if (!gpdata->queuecursor_handler)
    {
        gpdata->queuecursor_handler = IDLE_ADD ((GSourceFunc) remmina_plugin_rdpev_queuecursor, gp);
    }
}

static void
remmina_plugin_rdpui_scale_area (RemminaProtocolWidget *gp, gint *x, gint *y, gint *w, gint *h)
{
    RemminaPluginRdpData *gpdata;
    gint sx, sy, sw, sh;
    gint width, height;

    gpdata = GET_DATA (gp);
    if (gpdata->rgb_buffer == NULL || gpdata->scale_buffer == NULL) return;

    width = remmina_plugin_service->protocol_plugin_get_width (gp);
    height = remmina_plugin_service->protocol_plugin_get_height (gp);
    if (width == 0 || height == 0) return;

    if (gpdata->scale_width == width && gpdata->scale_height == height)
    {
        /* Same size, just copy the pixels */
        *x = MIN (MAX (0, *x), width - 1);
        *y = MIN (MAX (0, *y), height - 1);
        *w = MIN (width - *x, *w);
        *h = MIN (height - *y, *h);
        gdk_pixbuf_copy_area (gpdata->rgb_buffer, *x, *y, *w, *h, gpdata->scale_buffer, *x, *y);
        return;
    }

    /* We have to extend the scaled region one scaled pixel, to avoid gaps */
    sx = MIN (MAX (0, (*x) * gpdata->scale_width / width
        - gpdata->scale_width / width - 2), gpdata->scale_width - 1);
    sy = MIN (MAX (0, (*y) * gpdata->scale_height / height
        - gpdata->scale_height / height - 2), gpdata->scale_height - 1);
    sw = MIN (gpdata->scale_width - sx, (*w) * gpdata->scale_width / width
        + gpdata->scale_width / width + 4);
    sh = MIN (gpdata->scale_height - sy, (*h) * gpdata->scale_height / height
        + gpdata->scale_height / height + 4);

    gdk_pixbuf_scale (gpdata->rgb_buffer, gpdata->scale_buffer,
        sx, sy,
        sw, sh,
        0, 0,
        (double) gpdata->scale_width / (double) width,
        (double) gpdata->scale_height / (double) height,
        remmina_plugin_service->pref_get_scale_quality ());

    *x = sx; *y = sy; *w = sw; *h = sh;
}

void
remmina_plugin_rdpui_update_rect (RemminaProtocolWidget *gp, int x, int y, int w, int h)
{
    if (remmina_plugin_service->protocol_plugin_get_scale (gp))
    {
        remmina_plugin_rdpui_scale_area (gp, &x, &y, &w, &h);
    }
    remmina_plugin_rdpui_queuedraw (gp, x, y, w, h);
}

static void
remmina_plugin_rdpui_error (rdpInst *inst, char *text)
{
    remmina_plugin_service->log_printf ("[RDP]%s", text);
}

static void
remmina_plugin_rdpui_begin_update (rdpInst *inst)
{
}

static void
remmina_plugin_rdpui_end_update (rdpInst *inst)
{
}

static void
remmina_plugin_rdpui_desktop_save (rdpInst *inst, int offset, int x, int y,
    int cx, int cy)
{
    printf("ui_desktop_save:\n");
}

static void
remmina_plugin_rdpui_desktop_restore (rdpInst *inst, int offset, int x, int y,
    int cx, int cy)
{
    printf("ui_desktop_restore:\n");
}

static RD_HGLYPH
remmina_plugin_rdpui_create_glyph (rdpInst *inst, int width, int height, uint8 * data)
{
    RemminaGlyph *rg;
    gint size;

    rg = g_new0 (RemminaGlyph, 1);
    rg->width = width;
    rg->height = height;
    rg->rowstride = (width + 7) / 8;
    size = rg->rowstride * height;
    rg->data = g_new (guchar, size);
    memcpy (rg->data, data, size);
    /*g_print ("create_glyph %i %i %X\n", width, height, (int)rg);*/
    return rg;
}

static void
remmina_plugin_rdpui_destroy_glyph (rdpInst *inst, RD_HGLYPH glyph)
{
    RemminaGlyph *rg;

    rg = (RemminaGlyph *) glyph;
    g_free (rg->data);
    g_free (rg);
}

static RD_HBITMAP
remmina_plugin_rdpui_create_bitmap (rdpInst *inst, int width, int height, uint8 * data)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    GdkPixbuf *pixbuf;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    pixbuf = remmina_plugin_rdpui_bitmap_convert (gpdata, width, height, 0, FALSE, data);

    return (RD_HBITMAP) pixbuf;
}

static void
remmina_plugin_rdpui_paint_bitmap (rdpInst *inst, int x, int y, int cx, int cy, int width,
    int height, uint8 * data)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    GdkPixbuf *pixbuf;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    /*g_print ("ui_paint_bitmap %i %i %i %i %i %i\n", x, y, cx, cy, width, height);*/
    pixbuf = remmina_plugin_rdpui_bitmap_convert (gpdata, width, height, 0, FALSE, data);
    LOCK_BUFFER (TRUE)
    gdk_pixbuf_copy_area (pixbuf, 0, 0, cx, cy, gpdata->rgb_buffer, x, y);
    remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    UNLOCK_BUFFER (TRUE)
    g_object_unref (pixbuf);
}

static void
remmina_plugin_rdpui_destroy_bitmap (rdpInst *inst, RD_HBITMAP bmp)
{
    g_object_unref (GDK_PIXBUF (bmp));
}

static void
remmina_plugin_rdpui_line (rdpInst *inst, uint8 opcode, int startx, int starty, int endx,
    int endy, RD_PEN * pen)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    /*g_print ("ui_line %i %i %i %i %i %X\n", opcode, startx, starty, endx, endy, pen->color);*/
    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    gpdata->pattern_w = 1;
    gpdata->pattern_h = 1;
    remmina_plugin_rdpui_color_convert (gpdata, pen->color, gpdata->pattern);

    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_patline (gpdata, opcode - 1, startx, starty, endx, endy);
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, MIN (startx, endx), MIN (starty, endy),
            (endx >= startx ? endx - startx : startx - endx),
            (endy >= starty ? endy - starty : starty - endy));
    }
    UNLOCK_BUFFER (TRUE)

    gpdata->pattern_w = 0;
    gpdata->pattern_h = 0;
}

static void
remmina_plugin_rdpui_rect (rdpInst *inst, int x, int y, int cx, int cy, int color)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    guchar pixel[3];
    gint rowstride;
    guchar *buffer;
    gint ix, iy;

    /*g_print ("ui_rect %i %i %i %i %X\n", x, y, cx, cy, color);*/
    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    remmina_plugin_rdpui_color_convert (gpdata, color, pixel);
    remmina_plugin_rdpui_process_clip (gpdata, &x, &y, &cx, &cy, NULL, NULL);
    rowstride = gdk_pixbuf_get_rowstride (gpdata->drw_buffer);
    buffer = gdk_pixbuf_get_pixels (gpdata->drw_buffer) + y * rowstride + x * 3;
    LOCK_BUFFER (TRUE)
    for (iy = 0; iy < cy; iy++)
    {
        for (ix = 0; ix < cx; ix++)
        {
            memcpy (buffer + ix * 3, pixel, 3);
        }
        buffer += rowstride;
    }
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    }
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_polygon (rdpInst *inst, uint8 opcode, uint8 fillmode, RD_POINT * point,
    int npoints, RD_BRUSH * brush, int bgcolor, int fgcolor)
{
}

static void
remmina_plugin_rdpui_polyline (rdpInst *inst, uint8 opcode, RD_POINT * points, int npoints,
    RD_PEN * pen)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    gint i;
    gint x0, y0, x1, y1;
    gint dx0, dy0, dx1, dy1;

    /*g_print ("polyline: %i %X %i\n", opcode, pen->color, npoints);*/
    if (npoints < 2) return;
    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    gpdata->pattern_w = 1;
    gpdata->pattern_h = 1;
    remmina_plugin_rdpui_color_convert (gpdata, pen->color, gpdata->pattern);

    LOCK_BUFFER (TRUE)
    dx0 = x0 = x1 = points[0].x;
    dy0 = y0 = y1 = points[0].y;
    for (i = 1; i < npoints; i++)
    {
        dx1 = dx0 + points[i].x;
        dy1 = dy0 + points[i].y;
        remmina_plugin_rdpui_patline (gpdata, opcode - 1, dx0, dy0, dx1, dy1);
        x0 = MIN (x0, dx1);
        x1 = MAX (x1, dx1);
        y0 = MIN (y0, dy1);
        y1 = MAX (y1, dy1);
        dx0 = dx1;
        dy0 = dy1;
    }
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x0, y0, x1 - x0 + 1, y1 - y0 + 1);
    }
    UNLOCK_BUFFER (TRUE)

    gpdata->pattern_w = 0;
    gpdata->pattern_h = 0;
}

static void
remmina_plugin_rdpui_ellipse (rdpInst *inst, uint8 opcode, uint8 fillmode, int x, int y,
    int cx, int cy, RD_BRUSH * brush, int bgcolor, int fgcolor)
{
    g_print ("ellipse:\n");
}

static void
remmina_plugin_rdpui_start_draw_glyphs (rdpInst *inst, int bgcolor, int fgcolor)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    /*g_print ("start_draw_glyphs: %X %X\n", bgcolor, fgcolor);*/
    remmina_plugin_rdpui_color_convert (gpdata, bgcolor, gpdata->bgcolor);
    remmina_plugin_rdpui_color_convert (gpdata, fgcolor, gpdata->fgcolor);
}

static void
remmina_plugin_rdpui_draw_glyph (rdpInst *inst, int x, int y, int cx, int cy,
    RD_HGLYPH glyph)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    RemminaGlyph *rg;
    gint rowstride;
    guchar *buffer;
    gint ix, iy;
    gint srcx, srcy;
    guchar *rgdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    
    rg = (RemminaGlyph *) glyph;
    srcx = 0;
    srcy = 0;
    remmina_plugin_rdpui_process_clip_full (&x, &y, &cx, &cy, &srcx, &srcy,
        x, y, rg->width, rg->height);
    if (cx <= 0 || cy <= 0) return;
    remmina_plugin_rdpui_process_clip (gpdata, &x, &y, &cx, &cy, &srcx, &srcy);
    cx = MIN (cx, gdk_pixbuf_get_width (gpdata->drw_buffer) - x);
    cy = MIN (cy, gdk_pixbuf_get_height (gpdata->drw_buffer) - y);
    if (cx <= 0 || cy <= 0) return;
    /*g_print ("draw_glyph: %X %i %i %i %i %i %i %i %i %i %i\n", (int)glyph, x, y, cx, cy, srcx, srcy,
        rg->width, rg->height, gdk_pixbuf_get_width (gpdata->drw_buffer), gdk_pixbuf_get_height (gpdata->drw_buffer));*/
    rowstride = gdk_pixbuf_get_rowstride (gpdata->drw_buffer);
    LOCK_BUFFER (TRUE)
    for (iy = 0; iy < cy; iy++)
    {
        if (srcy + iy < 0 || y + iy < 0) continue;
        rgdata = rg->data + (srcy + iy) * rg->rowstride;
        buffer = gdk_pixbuf_get_pixels (gpdata->drw_buffer) + (y + iy) * rowstride + x * 3;
        for (ix = 0; ix < cx; ix++)
        {
            if (srcx + ix < 0 || x + ix < 0) continue;
            if (GLYPH_PIXEL (rgdata, srcx + ix))
            {
                memcpy (buffer + ix * 3, gpdata->fgcolor, 3);
            }
        }
    }
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_end_draw_glyphs (rdpInst *inst, int x, int y, int cx, int cy)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    /*g_print ("end_draw_glyphs %i %i %i %i\n", x, y, cx, cy);*/
    LOCK_BUFFER (TRUE)
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    }
    UNLOCK_BUFFER (TRUE)
}

static uint32
remmina_plugin_rdpui_get_toggle_keys_state (rdpInst *inst)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    uint32 state = 0;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    if (gpdata->capslock_initstate)
    {
        state |= KBD_SYNC_CAPS_LOCK;
    }
    if (gpdata->numlock_initstate)
    {
        state |= KBD_SYNC_NUM_LOCK;
    }
    
    return state;
}

static void
remmina_plugin_rdpui_bell (rdpInst *inst)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    THREADS_ENTER
    gdk_window_beep (gpdata->drawing_area->window);
    THREADS_LEAVE
}

static void
remmina_plugin_rdpui_destblt (rdpInst *inst, uint8 opcode, int x, int y, int cx, int cy)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    /*g_print ("destblt: %i %i %i %i %i\n", opcode, x, y, cx, cy);*/
    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_process_rop3 (gpdata, opcode, x, y, cx, cy, NULL, 0, 0);
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    }
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_patblt (rdpInst *inst, uint8 opcode, int x, int y, int cx, int cy,
    RD_BRUSH * brush, int bgcolor, int fgcolor)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    guchar *srcpat;
    GdkPixbuf *pixbuf;
    gint iy;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    /*g_print ("patblt %i %i %i %i opcode=%i style=%i fgcolor=%X \n", x, y, cx, cy, opcode, brush->style, fgcolor);*/
    remmina_plugin_rdpui_color_convert(gpdata, fgcolor, gpdata->fgcolor);
    remmina_plugin_rdpui_color_convert(gpdata, bgcolor, gpdata->bgcolor);

    LOCK_BUFFER (TRUE)
    switch (brush->style)
    {
    case 0: /* Solid */
        gpdata->pattern_w = 1;
        gpdata->pattern_h = 1;
        memcpy (gpdata->pattern, gpdata->fgcolor, 3);
        break;
    case 2: /* Hatch */
        if (brush->pattern[0] >= 0 && brush->pattern[0] <= 5)
        {
            srcpat = hatch_patterns + brush->pattern[0] * 8;
        }
        else
        {
            srcpat = hatch_patterns;
        }
        remmina_plugin_rdpui_fill_pattern (gpdata, srcpat, 0);
        break;
    case 3: /* Pattern */
        if (brush->bd == 0) /* rdp4 brush */
        {
            remmina_plugin_rdpui_fill_pattern (gpdata, brush->pattern, 1);
        }
        else if (brush->bd->color_code > 1) /* > 1 bpp */
        {
            gpdata->pattern_w = 8;
            gpdata->pattern_h = 8;
            pixbuf = remmina_plugin_rdpui_bitmap_convert (gpdata, 8, 8, 0, FALSE, brush->bd->data);
            for (iy = 0; iy < 8; iy++)
            {
                memcpy (gpdata->pattern + iy * 8 * 3,
                    gdk_pixbuf_get_pixels (pixbuf) + iy * gdk_pixbuf_get_rowstride (pixbuf),
                    8 * 3);
            }
            g_object_unref (pixbuf);
        }
        else
        {
            remmina_plugin_rdpui_fill_pattern (gpdata, brush->bd->data, 0);
        }
        break;
    default:
        gpdata->pattern_w = 0;
        gpdata->pattern_h = 0;
        remmina_plugin_service->log_printf ("[RDP]Unsupported brush style %i\n", brush->style);
        break;
    }
    remmina_plugin_rdpui_process_rop3 (gpdata, opcode, x, y, cx, cy, NULL, 0, 0);
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    }
    UNLOCK_BUFFER (TRUE)

    gpdata->pattern_w = 0;
    gpdata->pattern_h = 0;
}

static void
remmina_plugin_rdpui_screenblt (rdpInst *inst, uint8 opcode, int x, int y, int cx, int cy,
    int srcx, int srcy)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    /*g_print ("screenblt: %i %i %i %i %i %i %i\n", opcode, x, y, cx, cy, srcx, srcy);*/
    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_process_rop3 (gpdata, opcode, x, y, cx, cy, gpdata->rgb_buffer, srcx, srcy);
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    }
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_memblt (rdpInst *inst, uint8 opcode, int x, int y, int cx, int cy,
    RD_HBITMAP src, int srcx, int srcy)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    /*g_print ("memblt: %i %i %i %i %i %i %i\n", opcode, x, y, cx, cy, srcx, srcy);*/
    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_process_rop3 (gpdata, opcode, x, y, cx, cy, GDK_PIXBUF (src), srcx, srcy);
    if (gpdata->drw_buffer == gpdata->rgb_buffer)
    {
        remmina_plugin_rdpui_update_rect (gp, x, y, cx, cy);
    }
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_triblt (rdpInst *inst, uint8 opcode, int x, int y, int cx, int cy,
    RD_HBITMAP src, int srcx, int srcy, RD_BRUSH * brush, int bgcolor, int fgcolor)
{
}

static int
remmina_plugin_rdpui_select (rdpInst *inst, int rdp_socket)
{
    return 1;
}

static void
remmina_plugin_rdpui_set_clip (rdpInst *inst, int x, int y, int cx, int cy)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    /*g_print ("ui_set_clip %i %i %i %i\n", x, y, cx, cy);*/
    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    gpdata->clip_x = x;
    gpdata->clip_y = y;
    gpdata->clip_w = cx;
    gpdata->clip_h = cy;
    gpdata->clip = TRUE;
}

static void
remmina_plugin_rdpui_reset_clip (rdpInst *inst)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    /*g_print ("ui_reset_clip\n");*/
    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    gpdata->clip = FALSE;
}

static void
remmina_plugin_rdpui_resize_window (rdpInst *inst)
{
}

static void
remmina_plugin_rdpui_set_cursor (rdpInst *inst, RD_HCURSOR cursor)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    GdkPixbuf *pixbuf;
    gint x, y;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    pixbuf = GDK_PIXBUF (cursor);
    x = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (pixbuf), "x"));
    y = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (pixbuf), "y"));

    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_queuecursor (gp, pixbuf, FALSE, x, y);
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_destroy_cursor (rdpInst *inst, RD_HCURSOR cursor)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    LOCK_BUFFER (TRUE)
    if (gpdata->queuecursor_handler && GDK_PIXBUF (cursor) == gpdata->queuecursor_pixbuf)
    {
        g_source_remove (gpdata->queuecursor_handler);
        gpdata->queuecursor_handler = 0;
        gpdata->queuecursor_pixbuf = NULL;
    }
    UNLOCK_BUFFER (TRUE)
    g_object_unref (GDK_PIXBUF (cursor));
}

static RD_HCURSOR
remmina_plugin_rdpui_create_cursor (rdpInst *inst, uint32 x, uint32 y,
    int width, int height, uint8 * andmask, uint8 * xormask, int bpp)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    GdkPixbuf *pixbuf;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    /*g_print ("create_cursor %i %i %i %i %i\n", x, y, width, height, bpp);*/
    pixbuf = remmina_plugin_rdpui_bitmap_convert (gpdata, width, height, bpp, TRUE, xormask);
    remmina_plugin_rdpui_bitmap_apply_mask (pixbuf, andmask);
    if (bpp > 1)
    {
        remmina_plugin_rdpui_bitmap_flip (pixbuf);
    }
    g_object_set_data (G_OBJECT (pixbuf), "x", GINT_TO_POINTER (x));
    g_object_set_data (G_OBJECT (pixbuf), "y", GINT_TO_POINTER (y));
    return (RD_HCURSOR) pixbuf;
}

static void
remmina_plugin_rdpui_set_null_cursor (rdpInst *inst)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_queuecursor (gp, NULL, TRUE, 0, 0);
    UNLOCK_BUFFER (TRUE)
}

static void
remmina_plugin_rdpui_set_default_cursor (rdpInst *inst)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);

    LOCK_BUFFER (TRUE)
    remmina_plugin_rdpui_queuecursor (gp, NULL, FALSE, 0, 0);
    UNLOCK_BUFFER (TRUE)
}

static RD_HPALETTE
remmina_plugin_rdpui_create_colormap (rdpInst *inst, RD_PALETTE * colors)
{
    guchar *colormap;
    guchar *dst;
    gint count;
    gint i;

    colormap = g_new0 (guchar, 3 * 256);
    count = colors->ncolors;
    if (count > 256)
    {
        count = 256;
    }
    dst = colormap;
    for (i = 0; i < count; i++)
    {
        *dst++ = colors->colors[i].red;
        *dst++ = colors->colors[i].green;
        *dst++ = colors->colors[i].blue;
    }
    return (RD_HPALETTE) colormap;
}

static void
remmina_plugin_rdpui_move_pointer (rdpInst *inst, int x, int y)
{
}

static void
remmina_plugin_rdpui_set_colormap (rdpInst *inst, RD_HPALETTE map)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    if (gpdata->colormap)
    {
        g_free (gpdata->colormap);
    }
    gpdata->colormap = (guchar *) map;
}

static RD_HBITMAP
remmina_plugin_rdpui_create_surface (rdpInst *inst, int width, int height, RD_HBITMAP old_surface)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;
    GdkPixbuf *oldpix;
    GdkPixbuf *newpix;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    oldpix = (GdkPixbuf *) old_surface;
    newpix = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, width, height);
    gdk_pixbuf_fill (newpix, 0);
    if (oldpix)
    {
        width = MIN (width, gdk_pixbuf_get_width (oldpix));
        height = MIN (height, gdk_pixbuf_get_height (oldpix));
        gdk_pixbuf_copy_area (oldpix, 0, 0, width, height, newpix, 0, 0);
        if (gpdata->drw_buffer == oldpix)
        {
            gpdata->drw_buffer = newpix;
        }
        g_object_unref (oldpix);
    }
    /*g_print ("create_surface new %X old %X\n", (int)newpix, (int)oldpix);*/
    return newpix;
}

static void
remmina_plugin_rdpui_set_surface (rdpInst *inst, RD_HBITMAP surface)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    gpdata->drw_buffer = (surface ? GDK_PIXBUF (surface) : gpdata->rgb_buffer);
}

static void
remmina_plugin_rdpui_destroy_surface (rdpInst *inst, RD_HBITMAP surface)
{
    RemminaProtocolWidget *gp;
    RemminaPluginRdpData *gpdata;

    /*g_print ("destroy_surface %X\n", (int)surface);*/
    gp = GET_WIDGET (inst);
    gpdata = GET_DATA (gp);
    if (gpdata->drw_buffer == surface)
    {
        gpdata->drw_buffer = gpdata->rgb_buffer;
    }
    g_object_unref (GDK_PIXBUF (surface));
}

static void
remmina_plugin_rdpui_channel_data (rdpInst *inst, int chan_id, char * data, int data_size,
    int flags, int total_size)
{
    freerdp_chanman_data (inst, chan_id, data, data_size, flags, total_size);
}

/* Migrated from xfreerdp */
static gboolean
remmina_plugin_rdpui_get_key_state (KeyCode keycode, int state, XModifierKeymap *modmap)
{
    int modifierpos, key, keysymMask = 0;
    int offset;

    if (keycode == NoSymbol)
    {
        return FALSE;
    }
    for (modifierpos = 0; modifierpos < 8; modifierpos++)
    {
        offset = modmap->max_keypermod * modifierpos;
        for (key = 0; key < modmap->max_keypermod; key++)
        {
            if (modmap->modifiermap[offset + key] == keycode)
            {
                keysymMask |= 1 << modifierpos;
            }
        }
    }
    return (state & keysymMask) ? TRUE : FALSE;
}

void
remmina_plugin_rdpui_init (RemminaProtocolWidget *gp)
{
    RemminaPluginRdpData *gpdata;
    Display *display;
    Window wdummy;
    int dummy;
    uint32 state;
    gint keycode;
    XModifierKeymap *modmap;

    display = GDK_DISPLAY_XDISPLAY (gdk_display_get_default ());
    XQueryPointer(display, GDK_ROOT_WINDOW (), &wdummy, &wdummy, &dummy, &dummy,
        &dummy, &dummy, &state);
    modmap = XGetModifierMapping (display);

    gpdata = GET_DATA (gp);

    keycode = XKeysymToKeycode (display, XK_Caps_Lock);
    gpdata->capslock_initstate = remmina_plugin_rdpui_get_key_state (keycode, state, modmap);

    keycode = XKeysymToKeycode (display, XK_Num_Lock);
    gpdata->numlock_initstate = remmina_plugin_rdpui_get_key_state (keycode, state, modmap);
}

void
remmina_plugin_rdpui_pre_connect (RemminaProtocolWidget *gp)
{
    RemminaPluginRdpData *gpdata;
    rdpInst *inst;

    gpdata = GET_DATA (gp);
    inst = gpdata->inst;
    inst->ui_error = remmina_plugin_rdpui_error;
    inst->ui_warning = remmina_plugin_rdpui_error;
    inst->ui_unimpl = remmina_plugin_rdpui_error;
    inst->ui_begin_update = remmina_plugin_rdpui_begin_update;
    inst->ui_end_update = remmina_plugin_rdpui_end_update;
    inst->ui_desktop_save = remmina_plugin_rdpui_desktop_save;
    inst->ui_desktop_restore = remmina_plugin_rdpui_desktop_restore;
    inst->ui_create_bitmap = remmina_plugin_rdpui_create_bitmap;
    inst->ui_paint_bitmap = remmina_plugin_rdpui_paint_bitmap;
    inst->ui_destroy_bitmap = remmina_plugin_rdpui_destroy_bitmap;
    inst->ui_line = remmina_plugin_rdpui_line;
    inst->ui_rect = remmina_plugin_rdpui_rect;
    inst->ui_polygon = remmina_plugin_rdpui_polygon;
    inst->ui_polyline = remmina_plugin_rdpui_polyline;
    inst->ui_ellipse = remmina_plugin_rdpui_ellipse;
    inst->ui_start_draw_glyphs = remmina_plugin_rdpui_start_draw_glyphs;
    inst->ui_draw_glyph = remmina_plugin_rdpui_draw_glyph;
    inst->ui_end_draw_glyphs = remmina_plugin_rdpui_end_draw_glyphs;
    inst->ui_get_toggle_keys_state = remmina_plugin_rdpui_get_toggle_keys_state;
    inst->ui_bell = remmina_plugin_rdpui_bell;
    inst->ui_destblt = remmina_plugin_rdpui_destblt;
    inst->ui_patblt = remmina_plugin_rdpui_patblt;
    inst->ui_screenblt = remmina_plugin_rdpui_screenblt;
    inst->ui_memblt = remmina_plugin_rdpui_memblt;
    inst->ui_triblt = remmina_plugin_rdpui_triblt;
    inst->ui_create_glyph = remmina_plugin_rdpui_create_glyph;
    inst->ui_destroy_glyph = remmina_plugin_rdpui_destroy_glyph;
    inst->ui_select = remmina_plugin_rdpui_select;
    inst->ui_set_clip = remmina_plugin_rdpui_set_clip;
    inst->ui_reset_clip = remmina_plugin_rdpui_reset_clip;
    inst->ui_resize_window = remmina_plugin_rdpui_resize_window;
    inst->ui_set_cursor = remmina_plugin_rdpui_set_cursor;
    inst->ui_destroy_cursor = remmina_plugin_rdpui_destroy_cursor;
    inst->ui_create_cursor = remmina_plugin_rdpui_create_cursor;
    inst->ui_set_null_cursor = remmina_plugin_rdpui_set_null_cursor;
    inst->ui_set_default_cursor = remmina_plugin_rdpui_set_default_cursor;
    inst->ui_create_colormap = remmina_plugin_rdpui_create_colormap;
    inst->ui_move_pointer = remmina_plugin_rdpui_move_pointer;
    inst->ui_set_colormap = remmina_plugin_rdpui_set_colormap;
    inst->ui_create_surface = remmina_plugin_rdpui_create_surface;
    inst->ui_set_surface = remmina_plugin_rdpui_set_surface;
    inst->ui_destroy_surface = remmina_plugin_rdpui_destroy_surface;
    inst->ui_channel_data = remmina_plugin_rdpui_channel_data;

    gpdata->rgb_buffer = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8,
        gpdata->settings->width, gpdata->settings->height);
    gpdata->drw_buffer = gpdata->rgb_buffer;
}

void
remmina_plugin_rdpui_post_connect (RemminaProtocolWidget *gp)
{
    THREADS_ENTER
    remmina_plugin_rdpev_update_scale (gp);
    THREADS_LEAVE
}

void
remmina_plugin_rdpui_uninit (RemminaProtocolWidget *gp)
{
    RemminaPluginRdpData *gpdata;

    gpdata = GET_DATA (gp);
    if (gpdata->queuedraw_handler)
    {
        g_source_remove (gpdata->queuedraw_handler);
        gpdata->queuedraw_handler = 0;
    }
    if (gpdata->queuecursor_handler)
    {
        g_source_remove (gpdata->queuecursor_handler);
        gpdata->queuecursor_handler = 0;
    }
    if (gpdata->rgb_buffer)
    {
        g_object_unref (gpdata->rgb_buffer);
        gpdata->rgb_buffer = NULL;
    }
    if (gpdata->scale_buffer)
    {
        g_object_unref (gpdata->scale_buffer);
        gpdata->scale_buffer = NULL;
    }
    if (gpdata->colormap)
    {
        g_free (gpdata->colormap);
        gpdata->colormap = NULL;
    }
}

void
remmina_plugin_rdpui_get_fds (RemminaProtocolWidget *gp, void ** read_fds, int * read_count)
{
    RemminaPluginRdpData *gpdata;

    gpdata = GET_DATA (gp);
    if (gpdata->event_pipe[0] != -1)
    {
        read_fds[*read_count] = (void *) gpdata->event_pipe[0];
        (*read_count)++;
    }
}

int
remmina_plugin_rdpui_check_fds (RemminaProtocolWidget *gp)
{
    RemminaPluginRdpData *gpdata;
    RemminaPluginRdpEvent *event;
    gchar buf[100];

    gpdata = GET_DATA (gp);
    if (gpdata->event_queue == NULL) return 0;

    while ((event = (RemminaPluginRdpEvent *) g_async_queue_try_pop (gpdata->event_queue)) != NULL)
    {
        gpdata->inst->rdp_send_input(gpdata->inst,
            event->type, event->flag, event->param1, event->param2);
        g_free (event);
    }

    (void) read (gpdata->event_pipe[0], buf, sizeof (buf));
    return 0;
}


/* vim: set ts=8 :
 *
 * Copyright (c) 2010, Gerard Lledó Vives, gerard.lledo@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. See README and COPYING for
 * more details.
 * 
 *  from
 *
 *  linux/fs/ext4/ext4.h
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/include/linux/minix_fs.h
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 * 
 */

#ifndef EXT4_SUPER_H
#define EXT4_SUPER_H

#include "ext4_basic.h"

#define EXT4_BG_INODE_UNINIT	0x0001 /* Inode table/bitmap not in use */
#define EXT4_BG_BLOCK_UNINIT	0x0002 /* Block bitmap not in use */
#define EXT4_BG_INODE_ZEROED	0x0004 /* On-disk itable initialized to zero */

#define EXT4_MIN_BLOCK_SIZE		1024
#define EXT4_MIN_DESC_SIZE		32
#define EXT4_MIN_DESC_SIZE_64BIT	64
#define	EXT4_MAX_DESC_SIZE		EXT4_MIN_BLOCK_SIZE


#define EXT4_HAS_COMPAT_FEATURE(sb,mask)			\
	( (sb)->s_feature_compat & cpu_to_le32(mask) )
#define EXT4_HAS_RO_COMPAT_FEATURE(sb,mask)			\
	( (sb)->s_feature_ro_compat & cpu_to_le32(mask) )
#define EXT4_HAS_INCOMPAT_FEATURE(sb,mask)			\
	( (sb)->s_feature_incompat & cpu_to_le32(mask) )
#define EXT4_SET_COMPAT_FEATURE(sb,mask)			\
	(sb)->s_feature_compat |= cpu_to_le32(mask)
#define EXT4_SET_RO_COMPAT_FEATURE(sb,mask)			\
	(sb)->s_feature_ro_compat |= cpu_to_le32(mask)
#define EXT4_SET_INCOMPAT_FEATURE(sb,mask)			\
	(sb)->s_feature_incompat |= cpu_to_le32(mask)
#define EXT4_CLEAR_COMPAT_FEATURE(sb,mask)			\
	(sb)->s_feature_compat &= ~cpu_to_le32(mask)
#define EXT4_CLEAR_RO_COMPAT_FEATURE(sb,mask)			\
	(sb)->s_feature_ro_compat &= ~cpu_to_le32(mask)
#define EXT4_CLEAR_INCOMPAT_FEATURE(sb,mask)			\
	(sb)->s_feature_incompat &= ~cpu_to_le32(mask)

#define EXT4_FEATURE_COMPAT_DIR_PREALLOC	0x0001
#define EXT4_FEATURE_COMPAT_IMAGIC_INODES	0x0002
#define EXT4_FEATURE_COMPAT_HAS_JOURNAL		0x0004
#define EXT4_FEATURE_COMPAT_EXT_ATTR		0x0008
#define EXT4_FEATURE_COMPAT_RESIZE_INODE	0x0010
#define EXT4_FEATURE_COMPAT_DIR_INDEX		0x0020

#define EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER	0x0001
#define EXT4_FEATURE_RO_COMPAT_LARGE_FILE	0x0002
#define EXT4_FEATURE_RO_COMPAT_BTREE_DIR	0x0004
#define EXT4_FEATURE_RO_COMPAT_HUGE_FILE    0x0008
#define EXT4_FEATURE_RO_COMPAT_GDT_CSUM		0x0010
#define EXT4_FEATURE_RO_COMPAT_DIR_NLINK	0x0020
#define EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE	0x0040

#define EXT4_FEATURE_INCOMPAT_COMPRESSION	0x0001
#define EXT4_FEATURE_INCOMPAT_FILETYPE		0x0002
#define EXT4_FEATURE_INCOMPAT_RECOVER		0x0004 /* Needs recovery */
#define EXT4_FEATURE_INCOMPAT_JOURNAL_DEV	0x0008 /* Journal device */
#define EXT4_FEATURE_INCOMPAT_META_BG		0x0010
#define EXT4_FEATURE_INCOMPAT_EXTENTS		0x0040 /* extents support */
#define EXT4_FEATURE_INCOMPAT_64BIT         0x0080
#define EXT4_FEATURE_INCOMPAT_MMP           0x0100
#define EXT4_FEATURE_INCOMPAT_FLEX_BG		0x0200
#define EXT4_FEATURE_INCOMPAT_DIRDATA		0x1000  /* used by Lustre - ldiskfs */
#define EXT4_FEATURE_INCOMPAT_BG_USE_META_CSUM	0x2000 /* use crc32c for bg */
#define EXT4_FEATURE_INCOMPAT_LARGEDIR		0x4000 /* >2GB or 3-lvl htree */
#define EXT4_FEATURE_INCOMPAT_INLINEDATA	0x8000 /* data in inode */

#define EXT4_FEATURE_INCOMPAT_SUPP	(                       \
                    EXT4_FEATURE_INCOMPAT_FILETYPE|         \
					EXT4_FEATURE_INCOMPAT_RECOVER|          \
					EXT4_FEATURE_INCOMPAT_META_BG|          \
					EXT4_FEATURE_INCOMPAT_EXTENTS|          \
					EXT4_FEATURE_INCOMPAT_64BIT|            \
					EXT4_FEATURE_INCOMPAT_FLEX_BG)
#define EXT4_FEATURE_RO_COMPAT_SUPP	(                       \
                    EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER|    \
					EXT4_FEATURE_RO_COMPAT_LARGE_FILE|      \
					EXT4_FEATURE_RO_COMPAT_GDT_CSUM|        \
					EXT4_FEATURE_RO_COMPAT_DIR_NLINK |      \
					EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE |    \
					EXT4_FEATURE_RO_COMPAT_BTREE_DIR |      \
					EXT4_FEATURE_RO_COMPAT_HUGE_FILE)

/*
 * Structure of a blocks group descriptor
 */
struct ext4_group_desc
{
	__le32	bg_block_bitmap_lo;	/* Blocks bitmap block */
	__le32	bg_inode_bitmap_lo;	/* Inodes bitmap block */
	__le32	bg_inode_table_lo;	/* Inodes table block */
	__le16	bg_free_blocks_count_lo;/* Free blocks count */
	__le16	bg_free_inodes_count_lo;/* Free inodes count */
	__le16	bg_used_dirs_count_lo;	/* Directories count */
	__le16	bg_flags;		/* EXT4_BG_flags (INODE_UNINIT, etc) */
	__u32	bg_reserved[2];		/* Likely block/inode bitmap checksum */
	__le16  bg_itable_unused_lo;	/* Unused inodes count */
	__le16  bg_checksum;		/* crc16(sb_uuid+group+desc) */
	__le32	bg_block_bitmap_hi;	/* Blocks bitmap block MSB */
	__le32	bg_inode_bitmap_hi;	/* Inodes bitmap block MSB */
	__le32	bg_inode_table_hi;	/* Inodes table block MSB */
	__le16	bg_free_blocks_count_hi;/* Free blocks count MSB */
	__le16	bg_free_inodes_count_hi;/* Free inodes count MSB */
	__le16	bg_used_dirs_count_hi;	/* Directories count MSB */
	__le16  bg_itable_unused_hi;    /* Unused inodes count MSB */
	__u32	bg_reserved2[3];
};

/*
 * Structure of the super block
 */
struct ext4_super_block {
/*00*/	__le32	s_inodes_count;		/* Inodes count */
	__le32	s_blocks_count_lo;	/* Blocks count */
	__le32	s_r_blocks_count_lo;	/* Reserved blocks count */
	__le32	s_free_blocks_count_lo;	/* Free blocks count */
/*10*/	__le32	s_free_inodes_count;	/* Free inodes count */
	__le32	s_first_data_block;	/* First Data Block */
	__le32	s_log_block_size;	/* Block size */
	__le32	s_obso_log_frag_size;	/* Obsoleted fragment size */
/*20*/	__le32	s_blocks_per_group;	/* # Blocks per group */
	__le32	s_obso_frags_per_group;	/* Obsoleted fragments per group */
	__le32	s_inodes_per_group;	/* # Inodes per group */
	__le32	s_mtime;		/* Mount time */
/*30*/	__le32	s_wtime;		/* Write time */
	__le16	s_mnt_count;		/* Mount count */
	__le16	s_max_mnt_count;	/* Maximal mount count */
	__le16	s_magic;		/* Magic signature */
	__le16	s_state;		/* File system state */
	__le16	s_errors;		/* Behaviour when detecting errors */
	__le16	s_minor_rev_level;	/* minor revision level */
/*40*/	__le32	s_lastcheck;		/* time of last check */
	__le32	s_checkinterval;	/* max. time between checks */
	__le32	s_creator_os;		/* OS */
	__le32	s_rev_level;		/* Revision level */
/*50*/	__le16	s_def_resuid;		/* Default uid for reserved blocks */
	__le16	s_def_resgid;		/* Default gid for reserved blocks */
	/*
	 * These fields are for EXT4_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 *
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	__le32	s_first_ino;		/* First non-reserved inode */
	__le16  s_inode_size;		/* size of inode structure */
	__le16	s_block_group_nr;	/* block group # of this superblock */
	__le32	s_feature_compat;	/* compatible feature set */
/*60*/	__le32	s_feature_incompat;	/* incompatible feature set */
	__le32	s_feature_ro_compat;	/* readonly-compatible feature set */
/*68*/	__u8	s_uuid[16];		/* 128-bit uuid for volume */
/*78*/	char	s_volume_name[16];	/* volume name */
/*88*/	char	s_last_mounted[64];	/* directory where last mounted */
/*C8*/	__le32	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT4_FEATURE_COMPAT_DIR_PREALLOC flag is on.
	 */
	__u8	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
	__u8	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
	__le16	s_reserved_gdt_blocks;	/* Per group desc for online growth */
	/*
	 * Journaling support valid if EXT4_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
/*D0*/	__u8	s_journal_uuid[16];	/* uuid of journal superblock */
/*E0*/	__le32	s_journal_inum;		/* inode number of journal file */
	__le32	s_journal_dev;		/* device number of journal file */
	__le32	s_last_orphan;		/* start of list of inodes to delete */
	__le32	s_hash_seed[4];		/* HTREE hash seed */
	__u8	s_def_hash_version;	/* Default hash version to use */
	__u8	s_reserved_char_pad;
	__le16  s_desc_size;		/* size of group descriptor */
/*100*/	__le32	s_default_mount_opts;
	__le32	s_first_meta_bg;	/* First metablock block group */
	__le32	s_mkfs_time;		/* When the filesystem was created */
	__le32	s_jnl_blocks[17];	/* Backup of the journal inode */
	/* 64bit support valid if EXT4_FEATURE_COMPAT_64BIT */
/*150*/	__le32	s_blocks_count_hi;	/* Blocks count */
	__le32	s_r_blocks_count_hi;	/* Reserved blocks count */
	__le32	s_free_blocks_count_hi;	/* Free blocks count */
	__le16	s_min_extra_isize;	/* All inodes have at least # bytes */
	__le16	s_want_extra_isize; 	/* New inodes should reserve # bytes */
	__le32	s_flags;		/* Miscellaneous flags */
	__le16  s_raid_stride;		/* RAID stride */
	__le16  s_mmp_interval;         /* # seconds to wait in MMP checking */
	__le64  s_mmp_block;            /* Block for multi-mount protection */
	__le32  s_raid_stripe_width;    /* blocks on all data disks (N*stride)*/
	__u8	s_log_groups_per_flex;  /* FLEX_BG group size */
	__u8	s_reserved_char_pad2;
	__le16  s_reserved_pad;
	__le64	s_kbytes_written;	/* nr of lifetime kilobytes written */
	__u32   s_reserved[160];        /* Padding to the end of the block */
};

#endif

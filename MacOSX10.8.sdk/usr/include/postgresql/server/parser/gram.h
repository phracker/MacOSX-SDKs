/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     FCONST = 259,
     SCONST = 260,
     BCONST = 261,
     XCONST = 262,
     Op = 263,
     ICONST = 264,
     PARAM = 265,
     TYPECAST = 266,
     DOT_DOT = 267,
     COLON_EQUALS = 268,
     ABORT_P = 269,
     ABSOLUTE_P = 270,
     ACCESS = 271,
     ACTION = 272,
     ADD_P = 273,
     ADMIN = 274,
     AFTER = 275,
     AGGREGATE = 276,
     ALL = 277,
     ALSO = 278,
     ALTER = 279,
     ALWAYS = 280,
     ANALYSE = 281,
     ANALYZE = 282,
     AND = 283,
     ANY = 284,
     ARRAY = 285,
     AS = 286,
     ASC = 287,
     ASSERTION = 288,
     ASSIGNMENT = 289,
     ASYMMETRIC = 290,
     AT = 291,
     ATTRIBUTE = 292,
     AUTHORIZATION = 293,
     BACKWARD = 294,
     BEFORE = 295,
     BEGIN_P = 296,
     BETWEEN = 297,
     BIGINT = 298,
     BINARY = 299,
     BIT = 300,
     BOOLEAN_P = 301,
     BOTH = 302,
     BY = 303,
     CACHE = 304,
     CALLED = 305,
     CASCADE = 306,
     CASCADED = 307,
     CASE = 308,
     CAST = 309,
     CATALOG_P = 310,
     CHAIN = 311,
     CHAR_P = 312,
     CHARACTER = 313,
     CHARACTERISTICS = 314,
     CHECK = 315,
     CHECKPOINT = 316,
     CLASS = 317,
     CLOSE = 318,
     CLUSTER = 319,
     COALESCE = 320,
     COLLATE = 321,
     COLLATION = 322,
     COLUMN = 323,
     COMMENT = 324,
     COMMENTS = 325,
     COMMIT = 326,
     COMMITTED = 327,
     CONCURRENTLY = 328,
     CONFIGURATION = 329,
     CONNECTION = 330,
     CONSTRAINT = 331,
     CONSTRAINTS = 332,
     CONTENT_P = 333,
     CONTINUE_P = 334,
     CONVERSION_P = 335,
     COPY = 336,
     COST = 337,
     CREATE = 338,
     CROSS = 339,
     CSV = 340,
     CURRENT_P = 341,
     CURRENT_CATALOG = 342,
     CURRENT_DATE = 343,
     CURRENT_ROLE = 344,
     CURRENT_SCHEMA = 345,
     CURRENT_TIME = 346,
     CURRENT_TIMESTAMP = 347,
     CURRENT_USER = 348,
     CURSOR = 349,
     CYCLE = 350,
     DATA_P = 351,
     DATABASE = 352,
     DAY_P = 353,
     DEALLOCATE = 354,
     DEC = 355,
     DECIMAL_P = 356,
     DECLARE = 357,
     DEFAULT = 358,
     DEFAULTS = 359,
     DEFERRABLE = 360,
     DEFERRED = 361,
     DEFINER = 362,
     DELETE_P = 363,
     DELIMITER = 364,
     DELIMITERS = 365,
     DESC = 366,
     DICTIONARY = 367,
     DISABLE_P = 368,
     DISCARD = 369,
     DISTINCT = 370,
     DO = 371,
     DOCUMENT_P = 372,
     DOMAIN_P = 373,
     DOUBLE_P = 374,
     DROP = 375,
     EACH = 376,
     ELSE = 377,
     ENABLE_P = 378,
     ENCODING = 379,
     ENCRYPTED = 380,
     END_P = 381,
     ENUM_P = 382,
     ESCAPE = 383,
     EXCEPT = 384,
     EXCLUDE = 385,
     EXCLUDING = 386,
     EXCLUSIVE = 387,
     EXECUTE = 388,
     EXISTS = 389,
     EXPLAIN = 390,
     EXTENSION = 391,
     EXTERNAL = 392,
     EXTRACT = 393,
     FALSE_P = 394,
     FAMILY = 395,
     FETCH = 396,
     FIRST_P = 397,
     FLOAT_P = 398,
     FOLLOWING = 399,
     FOR = 400,
     FORCE = 401,
     FOREIGN = 402,
     FORWARD = 403,
     FREEZE = 404,
     FROM = 405,
     FULL = 406,
     FUNCTION = 407,
     FUNCTIONS = 408,
     GLOBAL = 409,
     GRANT = 410,
     GRANTED = 411,
     GREATEST = 412,
     GROUP_P = 413,
     HANDLER = 414,
     HAVING = 415,
     HEADER_P = 416,
     HOLD = 417,
     HOUR_P = 418,
     IDENTITY_P = 419,
     IF_P = 420,
     ILIKE = 421,
     IMMEDIATE = 422,
     IMMUTABLE = 423,
     IMPLICIT_P = 424,
     IN_P = 425,
     INCLUDING = 426,
     INCREMENT = 427,
     INDEX = 428,
     INDEXES = 429,
     INHERIT = 430,
     INHERITS = 431,
     INITIALLY = 432,
     INLINE_P = 433,
     INNER_P = 434,
     INOUT = 435,
     INPUT_P = 436,
     INSENSITIVE = 437,
     INSERT = 438,
     INSTEAD = 439,
     INT_P = 440,
     INTEGER = 441,
     INTERSECT = 442,
     INTERVAL = 443,
     INTO = 444,
     INVOKER = 445,
     IS = 446,
     ISNULL = 447,
     ISOLATION = 448,
     JOIN = 449,
     KEY = 450,
     LABEL = 451,
     LANGUAGE = 452,
     LARGE_P = 453,
     LAST_P = 454,
     LC_COLLATE_P = 455,
     LC_CTYPE_P = 456,
     LEADING = 457,
     LEAST = 458,
     LEFT = 459,
     LEVEL = 460,
     LIKE = 461,
     LIMIT = 462,
     LISTEN = 463,
     LOAD = 464,
     LOCAL = 465,
     LOCALTIME = 466,
     LOCALTIMESTAMP = 467,
     LOCATION = 468,
     LOCK_P = 469,
     MAPPING = 470,
     MATCH = 471,
     MAXVALUE = 472,
     MINUTE_P = 473,
     MINVALUE = 474,
     MODE = 475,
     MONTH_P = 476,
     MOVE = 477,
     NAME_P = 478,
     NAMES = 479,
     NATIONAL = 480,
     NATURAL = 481,
     NCHAR = 482,
     NEXT = 483,
     NO = 484,
     NONE = 485,
     NOT = 486,
     NOTHING = 487,
     NOTIFY = 488,
     NOTNULL = 489,
     NOWAIT = 490,
     NULL_P = 491,
     NULLIF = 492,
     NULLS_P = 493,
     NUMERIC = 494,
     OBJECT_P = 495,
     OF = 496,
     OFF = 497,
     OFFSET = 498,
     OIDS = 499,
     ON = 500,
     ONLY = 501,
     OPERATOR = 502,
     OPTION = 503,
     OPTIONS = 504,
     OR = 505,
     ORDER = 506,
     OUT_P = 507,
     OUTER_P = 508,
     OVER = 509,
     OVERLAPS = 510,
     OVERLAY = 511,
     OWNED = 512,
     OWNER = 513,
     PARSER = 514,
     PARTIAL = 515,
     PARTITION = 516,
     PASSING = 517,
     PASSWORD = 518,
     PLACING = 519,
     PLANS = 520,
     POSITION = 521,
     PRECEDING = 522,
     PRECISION = 523,
     PRESERVE = 524,
     PREPARE = 525,
     PREPARED = 526,
     PRIMARY = 527,
     PRIOR = 528,
     PRIVILEGES = 529,
     PROCEDURAL = 530,
     PROCEDURE = 531,
     QUOTE = 532,
     RANGE = 533,
     READ = 534,
     REAL = 535,
     REASSIGN = 536,
     RECHECK = 537,
     RECURSIVE = 538,
     REF = 539,
     REFERENCES = 540,
     REINDEX = 541,
     RELATIVE_P = 542,
     RELEASE = 543,
     RENAME = 544,
     REPEATABLE = 545,
     REPLACE = 546,
     REPLICA = 547,
     RESET = 548,
     RESTART = 549,
     RESTRICT = 550,
     RETURNING = 551,
     RETURNS = 552,
     REVOKE = 553,
     RIGHT = 554,
     ROLE = 555,
     ROLLBACK = 556,
     ROW = 557,
     ROWS = 558,
     RULE = 559,
     SAVEPOINT = 560,
     SCHEMA = 561,
     SCROLL = 562,
     SEARCH = 563,
     SECOND_P = 564,
     SECURITY = 565,
     SELECT = 566,
     SEQUENCE = 567,
     SEQUENCES = 568,
     SERIALIZABLE = 569,
     SERVER = 570,
     SESSION = 571,
     SESSION_USER = 572,
     SET = 573,
     SETOF = 574,
     SHARE = 575,
     SHOW = 576,
     SIMILAR = 577,
     SIMPLE = 578,
     SMALLINT = 579,
     SOME = 580,
     STABLE = 581,
     STANDALONE_P = 582,
     START = 583,
     STATEMENT = 584,
     STATISTICS = 585,
     STDIN = 586,
     STDOUT = 587,
     STORAGE = 588,
     STRICT_P = 589,
     STRIP_P = 590,
     SUBSTRING = 591,
     SYMMETRIC = 592,
     SYSID = 593,
     SYSTEM_P = 594,
     TABLE = 595,
     TABLES = 596,
     TABLESPACE = 597,
     TEMP = 598,
     TEMPLATE = 599,
     TEMPORARY = 600,
     TEXT_P = 601,
     THEN = 602,
     TIME = 603,
     TIMESTAMP = 604,
     TO = 605,
     TRAILING = 606,
     TRANSACTION = 607,
     TREAT = 608,
     TRIGGER = 609,
     TRIM = 610,
     TRUE_P = 611,
     TRUNCATE = 612,
     TRUSTED = 613,
     TYPE_P = 614,
     UNBOUNDED = 615,
     UNCOMMITTED = 616,
     UNENCRYPTED = 617,
     UNION = 618,
     UNIQUE = 619,
     UNKNOWN = 620,
     UNLISTEN = 621,
     UNLOGGED = 622,
     UNTIL = 623,
     UPDATE = 624,
     USER = 625,
     USING = 626,
     VACUUM = 627,
     VALID = 628,
     VALIDATE = 629,
     VALIDATOR = 630,
     VALUE_P = 631,
     VALUES = 632,
     VARCHAR = 633,
     VARIADIC = 634,
     VARYING = 635,
     VERBOSE = 636,
     VERSION_P = 637,
     VIEW = 638,
     VOLATILE = 639,
     WHEN = 640,
     WHERE = 641,
     WHITESPACE_P = 642,
     WINDOW = 643,
     WITH = 644,
     WITHOUT = 645,
     WORK = 646,
     WRAPPER = 647,
     WRITE = 648,
     XML_P = 649,
     XMLATTRIBUTES = 650,
     XMLCONCAT = 651,
     XMLELEMENT = 652,
     XMLEXISTS = 653,
     XMLFOREST = 654,
     XMLPARSE = 655,
     XMLPI = 656,
     XMLROOT = 657,
     XMLSERIALIZE = 658,
     YEAR_P = 659,
     YES_P = 660,
     ZONE = 661,
     NULLS_FIRST = 662,
     NULLS_LAST = 663,
     WITH_TIME = 664,
     POSTFIXOP = 665,
     UMINUS = 666
   };
#endif
/* Tokens.  */
#define IDENT 258
#define FCONST 259
#define SCONST 260
#define BCONST 261
#define XCONST 262
#define Op 263
#define ICONST 264
#define PARAM 265
#define TYPECAST 266
#define DOT_DOT 267
#define COLON_EQUALS 268
#define ABORT_P 269
#define ABSOLUTE_P 270
#define ACCESS 271
#define ACTION 272
#define ADD_P 273
#define ADMIN 274
#define AFTER 275
#define AGGREGATE 276
#define ALL 277
#define ALSO 278
#define ALTER 279
#define ALWAYS 280
#define ANALYSE 281
#define ANALYZE 282
#define AND 283
#define ANY 284
#define ARRAY 285
#define AS 286
#define ASC 287
#define ASSERTION 288
#define ASSIGNMENT 289
#define ASYMMETRIC 290
#define AT 291
#define ATTRIBUTE 292
#define AUTHORIZATION 293
#define BACKWARD 294
#define BEFORE 295
#define BEGIN_P 296
#define BETWEEN 297
#define BIGINT 298
#define BINARY 299
#define BIT 300
#define BOOLEAN_P 301
#define BOTH 302
#define BY 303
#define CACHE 304
#define CALLED 305
#define CASCADE 306
#define CASCADED 307
#define CASE 308
#define CAST 309
#define CATALOG_P 310
#define CHAIN 311
#define CHAR_P 312
#define CHARACTER 313
#define CHARACTERISTICS 314
#define CHECK 315
#define CHECKPOINT 316
#define CLASS 317
#define CLOSE 318
#define CLUSTER 319
#define COALESCE 320
#define COLLATE 321
#define COLLATION 322
#define COLUMN 323
#define COMMENT 324
#define COMMENTS 325
#define COMMIT 326
#define COMMITTED 327
#define CONCURRENTLY 328
#define CONFIGURATION 329
#define CONNECTION 330
#define CONSTRAINT 331
#define CONSTRAINTS 332
#define CONTENT_P 333
#define CONTINUE_P 334
#define CONVERSION_P 335
#define COPY 336
#define COST 337
#define CREATE 338
#define CROSS 339
#define CSV 340
#define CURRENT_P 341
#define CURRENT_CATALOG 342
#define CURRENT_DATE 343
#define CURRENT_ROLE 344
#define CURRENT_SCHEMA 345
#define CURRENT_TIME 346
#define CURRENT_TIMESTAMP 347
#define CURRENT_USER 348
#define CURSOR 349
#define CYCLE 350
#define DATA_P 351
#define DATABASE 352
#define DAY_P 353
#define DEALLOCATE 354
#define DEC 355
#define DECIMAL_P 356
#define DECLARE 357
#define DEFAULT 358
#define DEFAULTS 359
#define DEFERRABLE 360
#define DEFERRED 361
#define DEFINER 362
#define DELETE_P 363
#define DELIMITER 364
#define DELIMITERS 365
#define DESC 366
#define DICTIONARY 367
#define DISABLE_P 368
#define DISCARD 369
#define DISTINCT 370
#define DO 371
#define DOCUMENT_P 372
#define DOMAIN_P 373
#define DOUBLE_P 374
#define DROP 375
#define EACH 376
#define ELSE 377
#define ENABLE_P 378
#define ENCODING 379
#define ENCRYPTED 380
#define END_P 381
#define ENUM_P 382
#define ESCAPE 383
#define EXCEPT 384
#define EXCLUDE 385
#define EXCLUDING 386
#define EXCLUSIVE 387
#define EXECUTE 388
#define EXISTS 389
#define EXPLAIN 390
#define EXTENSION 391
#define EXTERNAL 392
#define EXTRACT 393
#define FALSE_P 394
#define FAMILY 395
#define FETCH 396
#define FIRST_P 397
#define FLOAT_P 398
#define FOLLOWING 399
#define FOR 400
#define FORCE 401
#define FOREIGN 402
#define FORWARD 403
#define FREEZE 404
#define FROM 405
#define FULL 406
#define FUNCTION 407
#define FUNCTIONS 408
#define GLOBAL 409
#define GRANT 410
#define GRANTED 411
#define GREATEST 412
#define GROUP_P 413
#define HANDLER 414
#define HAVING 415
#define HEADER_P 416
#define HOLD 417
#define HOUR_P 418
#define IDENTITY_P 419
#define IF_P 420
#define ILIKE 421
#define IMMEDIATE 422
#define IMMUTABLE 423
#define IMPLICIT_P 424
#define IN_P 425
#define INCLUDING 426
#define INCREMENT 427
#define INDEX 428
#define INDEXES 429
#define INHERIT 430
#define INHERITS 431
#define INITIALLY 432
#define INLINE_P 433
#define INNER_P 434
#define INOUT 435
#define INPUT_P 436
#define INSENSITIVE 437
#define INSERT 438
#define INSTEAD 439
#define INT_P 440
#define INTEGER 441
#define INTERSECT 442
#define INTERVAL 443
#define INTO 444
#define INVOKER 445
#define IS 446
#define ISNULL 447
#define ISOLATION 448
#define JOIN 449
#define KEY 450
#define LABEL 451
#define LANGUAGE 452
#define LARGE_P 453
#define LAST_P 454
#define LC_COLLATE_P 455
#define LC_CTYPE_P 456
#define LEADING 457
#define LEAST 458
#define LEFT 459
#define LEVEL 460
#define LIKE 461
#define LIMIT 462
#define LISTEN 463
#define LOAD 464
#define LOCAL 465
#define LOCALTIME 466
#define LOCALTIMESTAMP 467
#define LOCATION 468
#define LOCK_P 469
#define MAPPING 470
#define MATCH 471
#define MAXVALUE 472
#define MINUTE_P 473
#define MINVALUE 474
#define MODE 475
#define MONTH_P 476
#define MOVE 477
#define NAME_P 478
#define NAMES 479
#define NATIONAL 480
#define NATURAL 481
#define NCHAR 482
#define NEXT 483
#define NO 484
#define NONE 485
#define NOT 486
#define NOTHING 487
#define NOTIFY 488
#define NOTNULL 489
#define NOWAIT 490
#define NULL_P 491
#define NULLIF 492
#define NULLS_P 493
#define NUMERIC 494
#define OBJECT_P 495
#define OF 496
#define OFF 497
#define OFFSET 498
#define OIDS 499
#define ON 500
#define ONLY 501
#define OPERATOR 502
#define OPTION 503
#define OPTIONS 504
#define OR 505
#define ORDER 506
#define OUT_P 507
#define OUTER_P 508
#define OVER 509
#define OVERLAPS 510
#define OVERLAY 511
#define OWNED 512
#define OWNER 513
#define PARSER 514
#define PARTIAL 515
#define PARTITION 516
#define PASSING 517
#define PASSWORD 518
#define PLACING 519
#define PLANS 520
#define POSITION 521
#define PRECEDING 522
#define PRECISION 523
#define PRESERVE 524
#define PREPARE 525
#define PREPARED 526
#define PRIMARY 527
#define PRIOR 528
#define PRIVILEGES 529
#define PROCEDURAL 530
#define PROCEDURE 531
#define QUOTE 532
#define RANGE 533
#define READ 534
#define REAL 535
#define REASSIGN 536
#define RECHECK 537
#define RECURSIVE 538
#define REF 539
#define REFERENCES 540
#define REINDEX 541
#define RELATIVE_P 542
#define RELEASE 543
#define RENAME 544
#define REPEATABLE 545
#define REPLACE 546
#define REPLICA 547
#define RESET 548
#define RESTART 549
#define RESTRICT 550
#define RETURNING 551
#define RETURNS 552
#define REVOKE 553
#define RIGHT 554
#define ROLE 555
#define ROLLBACK 556
#define ROW 557
#define ROWS 558
#define RULE 559
#define SAVEPOINT 560
#define SCHEMA 561
#define SCROLL 562
#define SEARCH 563
#define SECOND_P 564
#define SECURITY 565
#define SELECT 566
#define SEQUENCE 567
#define SEQUENCES 568
#define SERIALIZABLE 569
#define SERVER 570
#define SESSION 571
#define SESSION_USER 572
#define SET 573
#define SETOF 574
#define SHARE 575
#define SHOW 576
#define SIMILAR 577
#define SIMPLE 578
#define SMALLINT 579
#define SOME 580
#define STABLE 581
#define STANDALONE_P 582
#define START 583
#define STATEMENT 584
#define STATISTICS 585
#define STDIN 586
#define STDOUT 587
#define STORAGE 588
#define STRICT_P 589
#define STRIP_P 590
#define SUBSTRING 591
#define SYMMETRIC 592
#define SYSID 593
#define SYSTEM_P 594
#define TABLE 595
#define TABLES 596
#define TABLESPACE 597
#define TEMP 598
#define TEMPLATE 599
#define TEMPORARY 600
#define TEXT_P 601
#define THEN 602
#define TIME 603
#define TIMESTAMP 604
#define TO 605
#define TRAILING 606
#define TRANSACTION 607
#define TREAT 608
#define TRIGGER 609
#define TRIM 610
#define TRUE_P 611
#define TRUNCATE 612
#define TRUSTED 613
#define TYPE_P 614
#define UNBOUNDED 615
#define UNCOMMITTED 616
#define UNENCRYPTED 617
#define UNION 618
#define UNIQUE 619
#define UNKNOWN 620
#define UNLISTEN 621
#define UNLOGGED 622
#define UNTIL 623
#define UPDATE 624
#define USER 625
#define USING 626
#define VACUUM 627
#define VALID 628
#define VALIDATE 629
#define VALIDATOR 630
#define VALUE_P 631
#define VALUES 632
#define VARCHAR 633
#define VARIADIC 634
#define VARYING 635
#define VERBOSE 636
#define VERSION_P 637
#define VIEW 638
#define VOLATILE 639
#define WHEN 640
#define WHERE 641
#define WHITESPACE_P 642
#define WINDOW 643
#define WITH 644
#define WITHOUT 645
#define WORK 646
#define WRAPPER 647
#define WRITE 648
#define XML_P 649
#define XMLATTRIBUTES 650
#define XMLCONCAT 651
#define XMLELEMENT 652
#define XMLEXISTS 653
#define XMLFOREST 654
#define XMLPARSE 655
#define XMLPI 656
#define XMLROOT 657
#define XMLSERIALIZE 658
#define YEAR_P 659
#define YES_P 660
#define ZONE 661
#define NULLS_FIRST 662
#define NULLS_LAST 663
#define WITH_TIME 664
#define POSTFIXOP 665
#define UMINUS 666




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 160 "gram.y"
{
	core_YYSTYPE		core_yystype;
	/* these fields must match core_YYSTYPE: */
	int					ival;
	char				*str;
	const char			*keyword;

	char				chr;
	bool				boolean;
	JoinType			jtype;
	DropBehavior		dbehavior;
	OnCommitAction		oncommit;
	List				*list;
	Node				*node;
	Value				*value;
	ObjectType			objtype;
	TypeName			*typnam;
	FunctionParameter   *fun_param;
	FunctionParameterMode fun_param_mode;
	FuncWithArgs		*funwithargs;
	DefElem				*defelt;
	SortBy				*sortby;
	WindowDef			*windef;
	JoinExpr			*jexpr;
	IndexElem			*ielem;
	Alias				*alias;
	RangeVar			*range;
	IntoClause			*into;
	WithClause			*with;
	A_Indices			*aind;
	ResTarget			*target;
	struct PrivTarget	*privtarget;
	AccessPriv			*accesspriv;
	InsertStmt			*istmt;
	VariableSetStmt		*vsetstmt;
}
/* Line 1529 of yacc.c.  */
#line 908 "gram.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



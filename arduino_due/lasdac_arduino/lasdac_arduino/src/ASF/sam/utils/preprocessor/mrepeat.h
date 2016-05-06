/**
 * \file
 *
 * \brief Preprocessor macro notRepeating utils.
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _MnotRepeat_H_
#define _MnotRepeat_H_

/**
 * \defgroup group_sam_utils_mnotRepeat Preprocessor - Macro notRepeat
 *
 * \ingroup group_sam_utils
 *
 * \{
 */

#include "preprocessor.h"


//! Maximal number of repetitions supported by MnotRepeat.
#define MnotRepeat_LIMIT   256

/*! \brief Macro notRepeat.
 *
 * This macro represents a horizontal repetition construct.
 *
 * \param count  The number of repetitious calls to macro. Valid values range from 0 to MnotRepeat_LIMIT.
 * \param macro  A binary operation of the form macro(n, data). This macro is expanded by MnotRepeat with
 *               the current repetition number and the auxiliary data argument.
 * \param data   Auxiliary data passed to macro.
 *
 * \return       <tt>macro(0, data) macro(1, data) ... macro(count - 1, data)</tt>
 */
#define MnotRepeat(count, macro, data)         TPASTE2(MnotRepeat, count)(macro, data)

#define MnotRepeat0(  macro, data)
#define MnotRepeat1(  macro, data)       MnotRepeat0(  macro, data)   macro(  0, data)
#define MnotRepeat2(  macro, data)       MnotRepeat1(  macro, data)   macro(  1, data)
#define MnotRepeat3(  macro, data)       MnotRepeat2(  macro, data)   macro(  2, data)
#define MnotRepeat4(  macro, data)       MnotRepeat3(  macro, data)   macro(  3, data)
#define MnotRepeat5(  macro, data)       MnotRepeat4(  macro, data)   macro(  4, data)
#define MnotRepeat6(  macro, data)       MnotRepeat5(  macro, data)   macro(  5, data)
#define MnotRepeat7(  macro, data)       MnotRepeat6(  macro, data)   macro(  6, data)
#define MnotRepeat8(  macro, data)       MnotRepeat7(  macro, data)   macro(  7, data)
#define MnotRepeat9(  macro, data)       MnotRepeat8(  macro, data)   macro(  8, data)
#define MnotRepeat10( macro, data)       MnotRepeat9(  macro, data)   macro(  9, data)
#define MnotRepeat11( macro, data)       MnotRepeat10( macro, data)   macro( 10, data)
#define MnotRepeat12( macro, data)       MnotRepeat11( macro, data)   macro( 11, data)
#define MnotRepeat13( macro, data)       MnotRepeat12( macro, data)   macro( 12, data)
#define MnotRepeat14( macro, data)       MnotRepeat13( macro, data)   macro( 13, data)
#define MnotRepeat15( macro, data)       MnotRepeat14( macro, data)   macro( 14, data)
#define MnotRepeat16( macro, data)       MnotRepeat15( macro, data)   macro( 15, data)
#define MnotRepeat17( macro, data)       MnotRepeat16( macro, data)   macro( 16, data)
#define MnotRepeat18( macro, data)       MnotRepeat17( macro, data)   macro( 17, data)
#define MnotRepeat19( macro, data)       MnotRepeat18( macro, data)   macro( 18, data)
#define MnotRepeat20( macro, data)       MnotRepeat19( macro, data)   macro( 19, data)
#define MnotRepeat21( macro, data)       MnotRepeat20( macro, data)   macro( 20, data)
#define MnotRepeat22( macro, data)       MnotRepeat21( macro, data)   macro( 21, data)
#define MnotRepeat23( macro, data)       MnotRepeat22( macro, data)   macro( 22, data)
#define MnotRepeat24( macro, data)       MnotRepeat23( macro, data)   macro( 23, data)
#define MnotRepeat25( macro, data)       MnotRepeat24( macro, data)   macro( 24, data)
#define MnotRepeat26( macro, data)       MnotRepeat25( macro, data)   macro( 25, data)
#define MnotRepeat27( macro, data)       MnotRepeat26( macro, data)   macro( 26, data)
#define MnotRepeat28( macro, data)       MnotRepeat27( macro, data)   macro( 27, data)
#define MnotRepeat29( macro, data)       MnotRepeat28( macro, data)   macro( 28, data)
#define MnotRepeat30( macro, data)       MnotRepeat29( macro, data)   macro( 29, data)
#define MnotRepeat31( macro, data)       MnotRepeat30( macro, data)   macro( 30, data)
#define MnotRepeat32( macro, data)       MnotRepeat31( macro, data)   macro( 31, data)
#define MnotRepeat33( macro, data)       MnotRepeat32( macro, data)   macro( 32, data)
#define MnotRepeat34( macro, data)       MnotRepeat33( macro, data)   macro( 33, data)
#define MnotRepeat35( macro, data)       MnotRepeat34( macro, data)   macro( 34, data)
#define MnotRepeat36( macro, data)       MnotRepeat35( macro, data)   macro( 35, data)
#define MnotRepeat37( macro, data)       MnotRepeat36( macro, data)   macro( 36, data)
#define MnotRepeat38( macro, data)       MnotRepeat37( macro, data)   macro( 37, data)
#define MnotRepeat39( macro, data)       MnotRepeat38( macro, data)   macro( 38, data)
#define MnotRepeat40( macro, data)       MnotRepeat39( macro, data)   macro( 39, data)
#define MnotRepeat41( macro, data)       MnotRepeat40( macro, data)   macro( 40, data)
#define MnotRepeat42( macro, data)       MnotRepeat41( macro, data)   macro( 41, data)
#define MnotRepeat43( macro, data)       MnotRepeat42( macro, data)   macro( 42, data)
#define MnotRepeat44( macro, data)       MnotRepeat43( macro, data)   macro( 43, data)
#define MnotRepeat45( macro, data)       MnotRepeat44( macro, data)   macro( 44, data)
#define MnotRepeat46( macro, data)       MnotRepeat45( macro, data)   macro( 45, data)
#define MnotRepeat47( macro, data)       MnotRepeat46( macro, data)   macro( 46, data)
#define MnotRepeat48( macro, data)       MnotRepeat47( macro, data)   macro( 47, data)
#define MnotRepeat49( macro, data)       MnotRepeat48( macro, data)   macro( 48, data)
#define MnotRepeat50( macro, data)       MnotRepeat49( macro, data)   macro( 49, data)
#define MnotRepeat51( macro, data)       MnotRepeat50( macro, data)   macro( 50, data)
#define MnotRepeat52( macro, data)       MnotRepeat51( macro, data)   macro( 51, data)
#define MnotRepeat53( macro, data)       MnotRepeat52( macro, data)   macro( 52, data)
#define MnotRepeat54( macro, data)       MnotRepeat53( macro, data)   macro( 53, data)
#define MnotRepeat55( macro, data)       MnotRepeat54( macro, data)   macro( 54, data)
#define MnotRepeat56( macro, data)       MnotRepeat55( macro, data)   macro( 55, data)
#define MnotRepeat57( macro, data)       MnotRepeat56( macro, data)   macro( 56, data)
#define MnotRepeat58( macro, data)       MnotRepeat57( macro, data)   macro( 57, data)
#define MnotRepeat59( macro, data)       MnotRepeat58( macro, data)   macro( 58, data)
#define MnotRepeat60( macro, data)       MnotRepeat59( macro, data)   macro( 59, data)
#define MnotRepeat61( macro, data)       MnotRepeat60( macro, data)   macro( 60, data)
#define MnotRepeat62( macro, data)       MnotRepeat61( macro, data)   macro( 61, data)
#define MnotRepeat63( macro, data)       MnotRepeat62( macro, data)   macro( 62, data)
#define MnotRepeat64( macro, data)       MnotRepeat63( macro, data)   macro( 63, data)
#define MnotRepeat65( macro, data)       MnotRepeat64( macro, data)   macro( 64, data)
#define MnotRepeat66( macro, data)       MnotRepeat65( macro, data)   macro( 65, data)
#define MnotRepeat67( macro, data)       MnotRepeat66( macro, data)   macro( 66, data)
#define MnotRepeat68( macro, data)       MnotRepeat67( macro, data)   macro( 67, data)
#define MnotRepeat69( macro, data)       MnotRepeat68( macro, data)   macro( 68, data)
#define MnotRepeat70( macro, data)       MnotRepeat69( macro, data)   macro( 69, data)
#define MnotRepeat71( macro, data)       MnotRepeat70( macro, data)   macro( 70, data)
#define MnotRepeat72( macro, data)       MnotRepeat71( macro, data)   macro( 71, data)
#define MnotRepeat73( macro, data)       MnotRepeat72( macro, data)   macro( 72, data)
#define MnotRepeat74( macro, data)       MnotRepeat73( macro, data)   macro( 73, data)
#define MnotRepeat75( macro, data)       MnotRepeat74( macro, data)   macro( 74, data)
#define MnotRepeat76( macro, data)       MnotRepeat75( macro, data)   macro( 75, data)
#define MnotRepeat77( macro, data)       MnotRepeat76( macro, data)   macro( 76, data)
#define MnotRepeat78( macro, data)       MnotRepeat77( macro, data)   macro( 77, data)
#define MnotRepeat79( macro, data)       MnotRepeat78( macro, data)   macro( 78, data)
#define MnotRepeat80( macro, data)       MnotRepeat79( macro, data)   macro( 79, data)
#define MnotRepeat81( macro, data)       MnotRepeat80( macro, data)   macro( 80, data)
#define MnotRepeat82( macro, data)       MnotRepeat81( macro, data)   macro( 81, data)
#define MnotRepeat83( macro, data)       MnotRepeat82( macro, data)   macro( 82, data)
#define MnotRepeat84( macro, data)       MnotRepeat83( macro, data)   macro( 83, data)
#define MnotRepeat85( macro, data)       MnotRepeat84( macro, data)   macro( 84, data)
#define MnotRepeat86( macro, data)       MnotRepeat85( macro, data)   macro( 85, data)
#define MnotRepeat87( macro, data)       MnotRepeat86( macro, data)   macro( 86, data)
#define MnotRepeat88( macro, data)       MnotRepeat87( macro, data)   macro( 87, data)
#define MnotRepeat89( macro, data)       MnotRepeat88( macro, data)   macro( 88, data)
#define MnotRepeat90( macro, data)       MnotRepeat89( macro, data)   macro( 89, data)
#define MnotRepeat91( macro, data)       MnotRepeat90( macro, data)   macro( 90, data)
#define MnotRepeat92( macro, data)       MnotRepeat91( macro, data)   macro( 91, data)
#define MnotRepeat93( macro, data)       MnotRepeat92( macro, data)   macro( 92, data)
#define MnotRepeat94( macro, data)       MnotRepeat93( macro, data)   macro( 93, data)
#define MnotRepeat95( macro, data)       MnotRepeat94( macro, data)   macro( 94, data)
#define MnotRepeat96( macro, data)       MnotRepeat95( macro, data)   macro( 95, data)
#define MnotRepeat97( macro, data)       MnotRepeat96( macro, data)   macro( 96, data)
#define MnotRepeat98( macro, data)       MnotRepeat97( macro, data)   macro( 97, data)
#define MnotRepeat99( macro, data)       MnotRepeat98( macro, data)   macro( 98, data)
#define MnotRepeat100(macro, data)       MnotRepeat99( macro, data)   macro( 99, data)
#define MnotRepeat101(macro, data)       MnotRepeat100(macro, data)   macro(100, data)
#define MnotRepeat102(macro, data)       MnotRepeat101(macro, data)   macro(101, data)
#define MnotRepeat103(macro, data)       MnotRepeat102(macro, data)   macro(102, data)
#define MnotRepeat104(macro, data)       MnotRepeat103(macro, data)   macro(103, data)
#define MnotRepeat105(macro, data)       MnotRepeat104(macro, data)   macro(104, data)
#define MnotRepeat106(macro, data)       MnotRepeat105(macro, data)   macro(105, data)
#define MnotRepeat107(macro, data)       MnotRepeat106(macro, data)   macro(106, data)
#define MnotRepeat108(macro, data)       MnotRepeat107(macro, data)   macro(107, data)
#define MnotRepeat109(macro, data)       MnotRepeat108(macro, data)   macro(108, data)
#define MnotRepeat110(macro, data)       MnotRepeat109(macro, data)   macro(109, data)
#define MnotRepeat111(macro, data)       MnotRepeat110(macro, data)   macro(110, data)
#define MnotRepeat112(macro, data)       MnotRepeat111(macro, data)   macro(111, data)
#define MnotRepeat113(macro, data)       MnotRepeat112(macro, data)   macro(112, data)
#define MnotRepeat114(macro, data)       MnotRepeat113(macro, data)   macro(113, data)
#define MnotRepeat115(macro, data)       MnotRepeat114(macro, data)   macro(114, data)
#define MnotRepeat116(macro, data)       MnotRepeat115(macro, data)   macro(115, data)
#define MnotRepeat117(macro, data)       MnotRepeat116(macro, data)   macro(116, data)
#define MnotRepeat118(macro, data)       MnotRepeat117(macro, data)   macro(117, data)
#define MnotRepeat119(macro, data)       MnotRepeat118(macro, data)   macro(118, data)
#define MnotRepeat120(macro, data)       MnotRepeat119(macro, data)   macro(119, data)
#define MnotRepeat121(macro, data)       MnotRepeat120(macro, data)   macro(120, data)
#define MnotRepeat122(macro, data)       MnotRepeat121(macro, data)   macro(121, data)
#define MnotRepeat123(macro, data)       MnotRepeat122(macro, data)   macro(122, data)
#define MnotRepeat124(macro, data)       MnotRepeat123(macro, data)   macro(123, data)
#define MnotRepeat125(macro, data)       MnotRepeat124(macro, data)   macro(124, data)
#define MnotRepeat126(macro, data)       MnotRepeat125(macro, data)   macro(125, data)
#define MnotRepeat127(macro, data)       MnotRepeat126(macro, data)   macro(126, data)
#define MnotRepeat128(macro, data)       MnotRepeat127(macro, data)   macro(127, data)
#define MnotRepeat129(macro, data)       MnotRepeat128(macro, data)   macro(128, data)
#define MnotRepeat130(macro, data)       MnotRepeat129(macro, data)   macro(129, data)
#define MnotRepeat131(macro, data)       MnotRepeat130(macro, data)   macro(130, data)
#define MnotRepeat132(macro, data)       MnotRepeat131(macro, data)   macro(131, data)
#define MnotRepeat133(macro, data)       MnotRepeat132(macro, data)   macro(132, data)
#define MnotRepeat134(macro, data)       MnotRepeat133(macro, data)   macro(133, data)
#define MnotRepeat135(macro, data)       MnotRepeat134(macro, data)   macro(134, data)
#define MnotRepeat136(macro, data)       MnotRepeat135(macro, data)   macro(135, data)
#define MnotRepeat137(macro, data)       MnotRepeat136(macro, data)   macro(136, data)
#define MnotRepeat138(macro, data)       MnotRepeat137(macro, data)   macro(137, data)
#define MnotRepeat139(macro, data)       MnotRepeat138(macro, data)   macro(138, data)
#define MnotRepeat140(macro, data)       MnotRepeat139(macro, data)   macro(139, data)
#define MnotRepeat141(macro, data)       MnotRepeat140(macro, data)   macro(140, data)
#define MnotRepeat142(macro, data)       MnotRepeat141(macro, data)   macro(141, data)
#define MnotRepeat143(macro, data)       MnotRepeat142(macro, data)   macro(142, data)
#define MnotRepeat144(macro, data)       MnotRepeat143(macro, data)   macro(143, data)
#define MnotRepeat145(macro, data)       MnotRepeat144(macro, data)   macro(144, data)
#define MnotRepeat146(macro, data)       MnotRepeat145(macro, data)   macro(145, data)
#define MnotRepeat147(macro, data)       MnotRepeat146(macro, data)   macro(146, data)
#define MnotRepeat148(macro, data)       MnotRepeat147(macro, data)   macro(147, data)
#define MnotRepeat149(macro, data)       MnotRepeat148(macro, data)   macro(148, data)
#define MnotRepeat150(macro, data)       MnotRepeat149(macro, data)   macro(149, data)
#define MnotRepeat151(macro, data)       MnotRepeat150(macro, data)   macro(150, data)
#define MnotRepeat152(macro, data)       MnotRepeat151(macro, data)   macro(151, data)
#define MnotRepeat153(macro, data)       MnotRepeat152(macro, data)   macro(152, data)
#define MnotRepeat154(macro, data)       MnotRepeat153(macro, data)   macro(153, data)
#define MnotRepeat155(macro, data)       MnotRepeat154(macro, data)   macro(154, data)
#define MnotRepeat156(macro, data)       MnotRepeat155(macro, data)   macro(155, data)
#define MnotRepeat157(macro, data)       MnotRepeat156(macro, data)   macro(156, data)
#define MnotRepeat158(macro, data)       MnotRepeat157(macro, data)   macro(157, data)
#define MnotRepeat159(macro, data)       MnotRepeat158(macro, data)   macro(158, data)
#define MnotRepeat160(macro, data)       MnotRepeat159(macro, data)   macro(159, data)
#define MnotRepeat161(macro, data)       MnotRepeat160(macro, data)   macro(160, data)
#define MnotRepeat162(macro, data)       MnotRepeat161(macro, data)   macro(161, data)
#define MnotRepeat163(macro, data)       MnotRepeat162(macro, data)   macro(162, data)
#define MnotRepeat164(macro, data)       MnotRepeat163(macro, data)   macro(163, data)
#define MnotRepeat165(macro, data)       MnotRepeat164(macro, data)   macro(164, data)
#define MnotRepeat166(macro, data)       MnotRepeat165(macro, data)   macro(165, data)
#define MnotRepeat167(macro, data)       MnotRepeat166(macro, data)   macro(166, data)
#define MnotRepeat168(macro, data)       MnotRepeat167(macro, data)   macro(167, data)
#define MnotRepeat169(macro, data)       MnotRepeat168(macro, data)   macro(168, data)
#define MnotRepeat170(macro, data)       MnotRepeat169(macro, data)   macro(169, data)
#define MnotRepeat171(macro, data)       MnotRepeat170(macro, data)   macro(170, data)
#define MnotRepeat172(macro, data)       MnotRepeat171(macro, data)   macro(171, data)
#define MnotRepeat173(macro, data)       MnotRepeat172(macro, data)   macro(172, data)
#define MnotRepeat174(macro, data)       MnotRepeat173(macro, data)   macro(173, data)
#define MnotRepeat175(macro, data)       MnotRepeat174(macro, data)   macro(174, data)
#define MnotRepeat176(macro, data)       MnotRepeat175(macro, data)   macro(175, data)
#define MnotRepeat177(macro, data)       MnotRepeat176(macro, data)   macro(176, data)
#define MnotRepeat178(macro, data)       MnotRepeat177(macro, data)   macro(177, data)
#define MnotRepeat179(macro, data)       MnotRepeat178(macro, data)   macro(178, data)
#define MnotRepeat180(macro, data)       MnotRepeat179(macro, data)   macro(179, data)
#define MnotRepeat181(macro, data)       MnotRepeat180(macro, data)   macro(180, data)
#define MnotRepeat182(macro, data)       MnotRepeat181(macro, data)   macro(181, data)
#define MnotRepeat183(macro, data)       MnotRepeat182(macro, data)   macro(182, data)
#define MnotRepeat184(macro, data)       MnotRepeat183(macro, data)   macro(183, data)
#define MnotRepeat185(macro, data)       MnotRepeat184(macro, data)   macro(184, data)
#define MnotRepeat186(macro, data)       MnotRepeat185(macro, data)   macro(185, data)
#define MnotRepeat187(macro, data)       MnotRepeat186(macro, data)   macro(186, data)
#define MnotRepeat188(macro, data)       MnotRepeat187(macro, data)   macro(187, data)
#define MnotRepeat189(macro, data)       MnotRepeat188(macro, data)   macro(188, data)
#define MnotRepeat190(macro, data)       MnotRepeat189(macro, data)   macro(189, data)
#define MnotRepeat191(macro, data)       MnotRepeat190(macro, data)   macro(190, data)
#define MnotRepeat192(macro, data)       MnotRepeat191(macro, data)   macro(191, data)
#define MnotRepeat193(macro, data)       MnotRepeat192(macro, data)   macro(192, data)
#define MnotRepeat194(macro, data)       MnotRepeat193(macro, data)   macro(193, data)
#define MnotRepeat195(macro, data)       MnotRepeat194(macro, data)   macro(194, data)
#define MnotRepeat196(macro, data)       MnotRepeat195(macro, data)   macro(195, data)
#define MnotRepeat197(macro, data)       MnotRepeat196(macro, data)   macro(196, data)
#define MnotRepeat198(macro, data)       MnotRepeat197(macro, data)   macro(197, data)
#define MnotRepeat199(macro, data)       MnotRepeat198(macro, data)   macro(198, data)
#define MnotRepeat200(macro, data)       MnotRepeat199(macro, data)   macro(199, data)
#define MnotRepeat201(macro, data)       MnotRepeat200(macro, data)   macro(200, data)
#define MnotRepeat202(macro, data)       MnotRepeat201(macro, data)   macro(201, data)
#define MnotRepeat203(macro, data)       MnotRepeat202(macro, data)   macro(202, data)
#define MnotRepeat204(macro, data)       MnotRepeat203(macro, data)   macro(203, data)
#define MnotRepeat205(macro, data)       MnotRepeat204(macro, data)   macro(204, data)
#define MnotRepeat206(macro, data)       MnotRepeat205(macro, data)   macro(205, data)
#define MnotRepeat207(macro, data)       MnotRepeat206(macro, data)   macro(206, data)
#define MnotRepeat208(macro, data)       MnotRepeat207(macro, data)   macro(207, data)
#define MnotRepeat209(macro, data)       MnotRepeat208(macro, data)   macro(208, data)
#define MnotRepeat210(macro, data)       MnotRepeat209(macro, data)   macro(209, data)
#define MnotRepeat211(macro, data)       MnotRepeat210(macro, data)   macro(210, data)
#define MnotRepeat212(macro, data)       MnotRepeat211(macro, data)   macro(211, data)
#define MnotRepeat213(macro, data)       MnotRepeat212(macro, data)   macro(212, data)
#define MnotRepeat214(macro, data)       MnotRepeat213(macro, data)   macro(213, data)
#define MnotRepeat215(macro, data)       MnotRepeat214(macro, data)   macro(214, data)
#define MnotRepeat216(macro, data)       MnotRepeat215(macro, data)   macro(215, data)
#define MnotRepeat217(macro, data)       MnotRepeat216(macro, data)   macro(216, data)
#define MnotRepeat218(macro, data)       MnotRepeat217(macro, data)   macro(217, data)
#define MnotRepeat219(macro, data)       MnotRepeat218(macro, data)   macro(218, data)
#define MnotRepeat220(macro, data)       MnotRepeat219(macro, data)   macro(219, data)
#define MnotRepeat221(macro, data)       MnotRepeat220(macro, data)   macro(220, data)
#define MnotRepeat222(macro, data)       MnotRepeat221(macro, data)   macro(221, data)
#define MnotRepeat223(macro, data)       MnotRepeat222(macro, data)   macro(222, data)
#define MnotRepeat224(macro, data)       MnotRepeat223(macro, data)   macro(223, data)
#define MnotRepeat225(macro, data)       MnotRepeat224(macro, data)   macro(224, data)
#define MnotRepeat226(macro, data)       MnotRepeat225(macro, data)   macro(225, data)
#define MnotRepeat227(macro, data)       MnotRepeat226(macro, data)   macro(226, data)
#define MnotRepeat228(macro, data)       MnotRepeat227(macro, data)   macro(227, data)
#define MnotRepeat229(macro, data)       MnotRepeat228(macro, data)   macro(228, data)
#define MnotRepeat230(macro, data)       MnotRepeat229(macro, data)   macro(229, data)
#define MnotRepeat231(macro, data)       MnotRepeat230(macro, data)   macro(230, data)
#define MnotRepeat232(macro, data)       MnotRepeat231(macro, data)   macro(231, data)
#define MnotRepeat233(macro, data)       MnotRepeat232(macro, data)   macro(232, data)
#define MnotRepeat234(macro, data)       MnotRepeat233(macro, data)   macro(233, data)
#define MnotRepeat235(macro, data)       MnotRepeat234(macro, data)   macro(234, data)
#define MnotRepeat236(macro, data)       MnotRepeat235(macro, data)   macro(235, data)
#define MnotRepeat237(macro, data)       MnotRepeat236(macro, data)   macro(236, data)
#define MnotRepeat238(macro, data)       MnotRepeat237(macro, data)   macro(237, data)
#define MnotRepeat239(macro, data)       MnotRepeat238(macro, data)   macro(238, data)
#define MnotRepeat240(macro, data)       MnotRepeat239(macro, data)   macro(239, data)
#define MnotRepeat241(macro, data)       MnotRepeat240(macro, data)   macro(240, data)
#define MnotRepeat242(macro, data)       MnotRepeat241(macro, data)   macro(241, data)
#define MnotRepeat243(macro, data)       MnotRepeat242(macro, data)   macro(242, data)
#define MnotRepeat244(macro, data)       MnotRepeat243(macro, data)   macro(243, data)
#define MnotRepeat245(macro, data)       MnotRepeat244(macro, data)   macro(244, data)
#define MnotRepeat246(macro, data)       MnotRepeat245(macro, data)   macro(245, data)
#define MnotRepeat247(macro, data)       MnotRepeat246(macro, data)   macro(246, data)
#define MnotRepeat248(macro, data)       MnotRepeat247(macro, data)   macro(247, data)
#define MnotRepeat249(macro, data)       MnotRepeat248(macro, data)   macro(248, data)
#define MnotRepeat250(macro, data)       MnotRepeat249(macro, data)   macro(249, data)
#define MnotRepeat251(macro, data)       MnotRepeat250(macro, data)   macro(250, data)
#define MnotRepeat252(macro, data)       MnotRepeat251(macro, data)   macro(251, data)
#define MnotRepeat253(macro, data)       MnotRepeat252(macro, data)   macro(252, data)
#define MnotRepeat254(macro, data)       MnotRepeat253(macro, data)   macro(253, data)
#define MnotRepeat255(macro, data)       MnotRepeat254(macro, data)   macro(254, data)
#define MnotRepeat256(macro, data)       MnotRepeat255(macro, data)   macro(255, data)

/**
 * \}
 */

#endif  // _MnotRepeat_H_

// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020, ARM Limited. All rights reserved.
 * Copyright (c) 2014, STMicroelectronics International N.V.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utee_defines.h>
#include <util.h>
#include <time.h>

#include "xtest_helpers.h"
#include "xtest_test.h"
#include "xtest_uuid_helpers.h"

/* VERSAL TESTS */
#define VERSAL_TEST_CMD_PMC_GPIO			0x00
#define VERSAL_TEST_CMD_PS_GPIO				0x01
#define VERSAL_TEST_CMD_NVM					0x10
#define VERSAL_TEST_CMD_PUF					0x20
#define VERSAL_TEST_CMD_PKI					0x40
#define VERSAL_TEST_CMD_BENCH_PKI			0x50
#define VERSAL_TEST_CMD_BENCH_PKI_CLIENT	0x60

static void versal_test_1000(ADBG_Case_t *c)
{
	TEEC_Result res = TEEC_ERROR_GENERIC;
	TEEC_Session session = { };
	uint32_t ret_orig = 0;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, NULL,
				      &ret_orig);
	if (res == TEEC_ERROR_ITEM_NOT_FOUND) {
		Do_ADBG_Log(" - 1000 -   skip test, pseudo TA not found");
		return;
	}
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PMC GPIO test");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_PMC_GPIO, NULL, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal PMC GPIO test");

	Do_ADBG_BeginSubCase(c, "Versal PS GPIO test");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_PS_GPIO, NULL, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal PS GPIO test");

	TEEC_CloseSession(&session);
}
ADBG_CASE_DEFINE(versal, 1000, versal_test_1000, "Versal Test GPIO");

static void versal_test_1010(ADBG_Case_t *c)
{
	TEEC_Result res = TEEC_ERROR_GENERIC;
	TEEC_Session session = { };
	uint32_t ret_orig = 0;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, NULL,
				      &ret_orig);
	if (res == TEEC_ERROR_ITEM_NOT_FOUND) {
		Do_ADBG_Log(" - 1010 -   skip test, pseudo TA not found");
		return;
	}
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal NVM test");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_NVM, NULL, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal NVM test");

	TEEC_CloseSession(&session);
}
ADBG_CASE_DEFINE(versal, 1010, versal_test_1010, "Versal Test NVM");

static void versal_test_1020(ADBG_Case_t *c)
{
	TEEC_Result res = TEEC_ERROR_GENERIC;
	TEEC_Session session = { };
	uint32_t ret_orig = 0;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, NULL,
				      &ret_orig);
	if (res == TEEC_ERROR_ITEM_NOT_FOUND) {
		Do_ADBG_Log(" - 1020 -   skip test, pseudo TA not found");
		return;
	}
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PUF test");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_PUF, NULL, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal PUF test");

	TEEC_CloseSession(&session);
}
ADBG_CASE_DEFINE(versal, 1020, versal_test_1020, "Versal Test PUF");

static void versal_test_1040(ADBG_Case_t *c)
{
	TEEC_Result res = TEEC_ERROR_GENERIC;
	TEEC_Session session = { };
	TEEC_Operation op = TEEC_OPERATION_INITIALIZER;
	uint32_t ret_orig = 0;

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P256;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (res == TEEC_ERROR_ITEM_NOT_FOUND) {
		Do_ADBG_Log(" - 1040 -   skip test, pseudo TA not found");
		return;
	}
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI - Sign/Verify P256");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_PKI, &op, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal PKI - Sign/Verify P256");

	TEEC_CloseSession(&session);

	op.params[0].value.a = TEE_ECC_CURVE_NIST_P384;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI - Sign/Verify P384");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_PKI, &op, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal PKI - Sign/Verify P384");

	TEEC_CloseSession(&session);

	op.params[0].value.a = TEE_ECC_CURVE_NIST_P521;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI - Sign/Verify P521");

	(void)ADBG_EXPECT_TEEC_SUCCESS(c, TEEC_InvokeCommand(
		&session, VERSAL_TEST_CMD_PKI, &op, &ret_orig));

	Do_ADBG_EndSubCase(c, "Versal PKI - Sign/Verify P521");

	TEEC_CloseSession(&session);
}
ADBG_CASE_DEFINE(versal, 1040, versal_test_1040, "Versal Test PKI");

#define OP_SIGN 	0
#define OP_VERIFY	1

#define LOOP_NUMBER 10

static void versal_test_1050(ADBG_Case_t *c)
{
	TEEC_Result res = TEEC_ERROR_GENERIC;
	TEEC_Session session = { };
	TEEC_Operation op = TEEC_OPERATION_INITIALIZER;
	uint32_t ret_orig = 0;

	uint32_t millis = 0;

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P256;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (res == TEEC_ERROR_ITEM_NOT_FOUND) {
		Do_ADBG_Log(" - 1050 -   skip test, pseudo TA not found");
		return;
	}
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Sign P256");

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P256;
	op.params[0].value.b = OP_SIGN;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI, &op,
					  &ret_orig);
		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		printf("P256 Sign operation %d took %" PRIu32 "ms to complete\n",
			i, op.params[1].value.a);
		millis += op.params[1].value.a;
	}

	printf("P256 Sign total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Sign P256");

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Verify P256");

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P256;
	op.params[0].value.b = OP_VERIFY;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI, &op,
					  &ret_orig);
		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		printf("P256 Sign operation %d took %" PRIu32 "ms to complete\n",
			i, op.params[1].value.a);
		millis += op.params[1].value.a;
	}

	printf("P256 Verify total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Verify P256");

	TEEC_CloseSession(&session);

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P384;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Sign P384");

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P384;
	op.params[0].value.b = OP_SIGN;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI, &op,
					  &ret_orig);
		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		printf("P384 Sign operation %d took %" PRIu32 "ms to complete\n",
			i, op.params[1].value.a);
		millis += op.params[1].value.a;
	}

	printf("P384 Sign total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Sign P384");

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Verify P384");

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P384;
	op.params[0].value.b = OP_VERIFY;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI, &op,
					  &ret_orig);
		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		printf("P384 Sign operation %d took %" PRIu32 "ms to complete\n",
			i, op.params[1].value.a);
		millis += op.params[1].value.a;
	}

	printf("P384 Verify total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Verify P384");

	TEEC_CloseSession(&session);

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P521;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Sign P521");

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P521;
	op.params[0].value.b = OP_SIGN;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI, &op,
					  &ret_orig);
		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		printf("P521 Sign operation %d took %" PRIu32 "ms to complete\n",
			i, op.params[1].value.a);
		millis += op.params[1].value.a;
	}

	printf("P521 Sign total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Sign P521");

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Verify P521");

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P521;
	op.params[0].value.b = OP_VERIFY;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI, &op,
					  &ret_orig);
		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		printf("P521 Sign operation %d took %" PRIu32 "ms to complete\n",
			i, op.params[1].value.a);
		millis += op.params[1].value.a;
	}

	printf("P521 Verify total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Verify P521");

	TEEC_CloseSession(&session);
}
ADBG_CASE_DEFINE(versal, 1050, versal_test_1050, "Versal Bench PKI ECDSA (server side)");

static void versal_test_1060(ADBG_Case_t *c)
{
	TEEC_Result res = TEEC_ERROR_GENERIC;
	TEEC_Session session = { };
	TEEC_Operation op = TEEC_OPERATION_INITIALIZER;
	uint32_t ret_orig = 0;

	uint32_t millis = 0;
	struct timespec start, end;

	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = TEE_ECC_CURVE_NIST_P256;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (res == TEEC_ERROR_ITEM_NOT_FOUND) {
		Do_ADBG_Log(" - 1060 -   skip test, pseudo TA not found");
		return;
	}
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Sign P256");

	op.params[0].value.b = OP_SIGN;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		uint32_t ms;

		clock_gettime(CLOCK_REALTIME, &start);

		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI_CLIENT, &op,
					  &ret_orig);

		clock_gettime(CLOCK_REALTIME, &end);

		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		ms = (end.tv_sec * 1000 + end.tv_nsec / 1000000)
			- (start.tv_sec * 1000 + start.tv_nsec / 1000000);

		printf("P256 Sign operation %d took %" PRIu32 "ms to complete\n", i, ms);

		millis += ms;
	}

	printf("P256 Sign total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Sign P256");

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Verify P256");

	op.params[0].value.b = OP_VERIFY;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		uint32_t ms;

		clock_gettime(CLOCK_REALTIME, &start);

		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI_CLIENT, &op,
					  &ret_orig);

		clock_gettime(CLOCK_REALTIME, &end);

		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		ms = (end.tv_sec * 1000 + end.tv_nsec / 1000000)
			- (start.tv_sec * 1000 + start.tv_nsec / 1000000);

		printf("P256 Verify operation %d took %" PRIu32 "ms to complete\n", i, ms);

		millis += ms;
	}

	printf("P256 Verify total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Verify P256");

	TEEC_CloseSession(&session);

	op.params[0].value.a = TEE_ECC_CURVE_NIST_P384;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Sign P384");

	op.params[0].value.b = OP_SIGN;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		uint32_t ms;

		clock_gettime(CLOCK_REALTIME, &start);

		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI_CLIENT, &op,
					  &ret_orig);

		clock_gettime(CLOCK_REALTIME, &end);

		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		ms = (end.tv_sec * 1000 + end.tv_nsec / 1000000)
			- (start.tv_sec * 1000 + start.tv_nsec / 1000000);

		printf("P384 Sign operation %d took %" PRIu32 "ms to complete\n", i, ms);

		millis += ms;
	}

	printf("P384 Sign total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Sign P384");

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Verify P384");

	op.params[0].value.b = OP_VERIFY;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		uint32_t ms;

		clock_gettime(CLOCK_REALTIME, &start);

		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI_CLIENT, &op,
					  &ret_orig);

		clock_gettime(CLOCK_REALTIME, &end);

		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		ms = (end.tv_sec * 1000 + end.tv_nsec / 1000000)
			- (start.tv_sec * 1000 + start.tv_nsec / 1000000);

		printf("P384 Verify operation %d took %" PRIu32 "ms to complete\n", i, ms);

		millis += ms;
	}

	printf("P384 Verify total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Verify P384");

	TEEC_CloseSession(&session);

	op.params[0].value.a = TEE_ECC_CURVE_NIST_P521;

	res = xtest_teec_open_session(&session, &versal_test_ta_uuid, &op,
				      &ret_orig);
	if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
		return;

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Sign P521");

	op.params[0].value.b = OP_SIGN;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		uint32_t ms;

		clock_gettime(CLOCK_REALTIME, &start);

		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI_CLIENT, &op,
					  &ret_orig);

		clock_gettime(CLOCK_REALTIME, &end);

		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		ms = (end.tv_sec * 1000 + end.tv_nsec / 1000000)
			- (start.tv_sec * 1000 + start.tv_nsec / 1000000);

		printf("P521 Sign operation %d took %" PRIu32 "ms to complete\n", i, ms);

		millis += ms;
	}

	printf("P521 Sign total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Sign P521");

	Do_ADBG_BeginSubCase(c, "Versal PKI Bench Verify P521");

	op.params[0].value.b = OP_VERIFY;

	millis = 0;

	for (int i = 0; i < LOOP_NUMBER; i++) {
		uint32_t ms;

		clock_gettime(CLOCK_REALTIME, &start);

		res = TEEC_InvokeCommand(&session, VERSAL_TEST_CMD_BENCH_PKI_CLIENT, &op,
					  &ret_orig);

		clock_gettime(CLOCK_REALTIME, &end);

		if (!ADBG_EXPECT_TEEC_SUCCESS(c, res))
			break;

		ms = (end.tv_sec * 1000 + end.tv_nsec / 1000000)
			- (start.tv_sec * 1000 + start.tv_nsec / 1000000);

		printf("P521 Verify operation %d took %" PRIu32 "ms to complete\n", i, ms);

		millis += ms;
	}

	printf("P521 Verify total time is %" PRIu32 "ms.\n", millis);

	Do_ADBG_EndSubCase(c, "Versal PKI Bench Verify P521");

	TEEC_CloseSession(&session);
}
ADBG_CASE_DEFINE(versal, 1060, versal_test_1060, "Versal Bench PKI ECDSA (client side)");

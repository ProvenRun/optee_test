// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2015, Linaro Limited

 */

#include <tee_ta_api.h>
#include <trace.h>

#include "ta_crypto_perf.h"
#include "ta_crypto_perf_priv.h"

/*
 * Trusted Application Entry Points
 */

/* Called each time a new instance is created */
TEE_Result TA_CreateEntryPoint(void)
{
	return TEE_SUCCESS;
}

/* Called each time an instance is destroyed */
void TA_DestroyEntryPoint(void)
{
}

/* Called each time a session is opened */
TEE_Result TA_OpenSessionEntryPoint(uint32_t nParamTypes,
				    TEE_Param pParams[4],
				    void **ppSessionContext)
{
	(void)nParamTypes;
	(void)pParams;
	(void)ppSessionContext;
	return TEE_SUCCESS;
}

/* Called each time a session is closed */
void TA_CloseSessionEntryPoint(void *pSessionContext)
{
	(void)pSessionContext;

	cmd_clean_res();
}

/* Called when a command is invoked */
TEE_Result TA_InvokeCommandEntryPoint(void *pSessionContext,
				      uint32_t nCommandID, uint32_t nParamTypes,
				      TEE_Param pParams[4])
{
	(void)pSessionContext;

	switch (nCommandID) {
	case TA_CRYPTO_PERF_CMD_CIPHER_PREPARE_KEY:
		return cmd_cipher_prepare_key(nParamTypes, pParams);

	case TA_CRYPTO_PERF_CMD_CIPHER_PROCESS:
		return cmd_cipher_process(nParamTypes, pParams, false);
	case TA_CRYPTO_PERF_CMD_CIPHER_PROCESS_SDP:
#ifdef CFG_SECURE_DATA_PATH
		return cmd_cipher_process(nParamTypes, pParams, true);
#else
		EMSG("Invalid SDP commands: TA was built without SDP support");
		return TEE_ERROR_NOT_SUPPORTED;
#endif
	case TA_CRYPTO_PERF_CMD_HASH_PREPARE_OP:
		return cmd_hash_prepare_op(nParamTypes, pParams);
	case TA_CRYPTO_PERF_CMD_HASH_PROCESS:
		return cmd_hash_process(nParamTypes, pParams);

	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}
}

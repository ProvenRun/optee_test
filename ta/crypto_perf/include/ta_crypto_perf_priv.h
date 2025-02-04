/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2015, Linaro Limited
 */

#ifndef TA_CRYPTO_PERF_PRIV_H
#define TA_CRYPTO_PERF_PRIV_H

#include <tee_api.h>

TEE_Result cmd_cipher_prepare_key(uint32_t param_types, TEE_Param params[4]);
TEE_Result cmd_cipher_process(uint32_t param_types, TEE_Param params[4],
			      bool sdp);
TEE_Result cmd_hash_prepare_op(uint32_t param_types, TEE_Param params[4]);
TEE_Result cmd_hash_process(uint32_t param_types, TEE_Param params[4]);
void cmd_clean_res(void);

#endif /* TA_CRYPTO_PERF_PRIV_H */

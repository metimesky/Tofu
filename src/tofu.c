/*
 * (Yet another) C web framework
 *
 * Copyright (c) 2011, Alessandro Ghedini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of the Tofu project, Alessandro Ghedini, nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include "ctx.h"
#include "rep.h"
#include "req.h"
#include "backend.h"

void tofu_loop(tofu_ctx_t *ctx) {
	tofu_backend_t backend;

#ifdef HAVE_FCGI_STDIO_H
	extern tofu_backend_t tofu_backend_fcgi;
#endif

#ifdef HAVE_ZMQ_H
	extern tofu_backend_t tofu_backend_zmq;
#endif

#ifdef HAVE_EVHTTP_H
	extern tofu_backend_t tofu_backend_evhttp;
#endif

	switch (ctx -> backend) {
#ifdef HAVE_FCGI_STDIO_H
		case BACKEND_FCGI:
			backend = tofu_backend_fcgi;
			break;
#endif

#ifdef HAVE_ZMQ_H
		case BACKEND_ZMQ:
			backend = tofu_backend_zmq;
			break;
#endif

#ifdef HAVE_EVHTTP_H
		case BACKEND_EVHTTP:
			backend = tofu_backend_evhttp;
			break;
#endif

		default: {
			fprintf(stderr, "Err: unknown backend\n");
			exit(-1);
		}
	}

	backend.loop(ctx);
}


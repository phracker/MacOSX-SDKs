/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MODPERL_CGI_H
#define MODPERL_CGI_H

/**
 * split the HTTP headers from the body (if any) and feed them to
 * Apache. Populate the pointer to the remaining data in the buffer
 * (body if any or NULL)
 *
 * @param r       request_rec
 * @param buffer  a string with headers and potentially body
 *                (could be non-null terminated)
 * @param len     length of 'buffer' on entry
 *                length of 'body' on return
 * @param body    pointer to the body within the 'buffer' on return
 *                NULL if the buffer contained only headers
 *
 * @return status
 */
MP_INLINE int modperl_cgi_header_parse(request_rec *r, char *buffer,
                                       apr_size_t *len, const char **body);

#endif /* MODPERL_CGI_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */

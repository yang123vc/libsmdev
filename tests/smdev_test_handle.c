/*
 * Library handle type testing program
 *
 * Copyright (C) 2010-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "smdev_test_libcerror.h"
#include "smdev_test_libclocale.h"
#include "smdev_test_libcsystem.h"
#include "smdev_test_libsmdev.h"
#include "smdev_test_libuna.h"
#include "smdev_test_macros.h"
#include "smdev_test_memory.h"

#if SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make smdev_test_handle generate verbose output
#define SMDEV_TEST_HANDLE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int smdev_test_handle_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "smdev_test_handle_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int smdev_test_handle_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "smdev_test_handle_get_wide_source";
	size_t wide_source_size = 0;
	size_t source_length    = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source handle
 * Returns 1 if successful or -1 on error
 */
int smdev_test_handle_open_source(
     libsmdev_handle_t **handle,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "smdev_test_handle_open_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libsmdev_handle_initialize(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libsmdev_handle_open_wide(
	          *handle,
	          source,
	          LIBSMDEV_OPEN_READ,
	          error );
#else
	result = libsmdev_handle_open(
	          *handle,
	          source,
	          LIBSMDEV_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *handle != NULL )
	{
		libsmdev_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source handle
 * Returns 1 if successful or -1 on error
 */
int smdev_test_handle_close_source(
     libsmdev_handle_t **handle,
     libcerror_error_t **error )
{
	static char *function = "smdev_test_handle_close_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( libsmdev_handle_close(
	     *handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close handle.",
		 function );

		result = -1;
	}
	if( libsmdev_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libsmdev_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libsmdev_handle_t *handle      = NULL;
	int result               = 0;

	/* Test libsmdev_handle_initialize
	 */
	result = libsmdev_handle_initialize(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libsmdev_handle_free(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libsmdev_handle_initialize(
	          NULL,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	handle = (libsmdev_handle_t *) 0x12345678UL;

	result = libsmdev_handle_initialize(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	handle = NULL;

#if defined( HAVE_SMDEV_TEST_MEMORY )

	/* Test libsmdev_handle_initialize with malloc failing
	 */
	smdev_test_malloc_attempts_before_fail = 0;

	result = libsmdev_handle_initialize(
	          &handle,
	          &error );

	if( smdev_test_malloc_attempts_before_fail != -1 )
	{
		smdev_test_malloc_attempts_before_fail = -1;

		if( handle != NULL )
		{
			libsmdev_handle_free(
			 &handle,
			 NULL );
		}
	}
	else
	{
		SMDEV_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		SMDEV_TEST_ASSERT_IS_NULL(
		 "handle",
		 handle );

		SMDEV_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libsmdev_handle_initialize with memset failing
	 */
	smdev_test_memset_attempts_before_fail = 0;

	result = libsmdev_handle_initialize(
	          &handle,
	          &error );

	if( smdev_test_memset_attempts_before_fail != -1 )
	{
		smdev_test_memset_attempts_before_fail = -1;

		if( handle != NULL )
		{
			libsmdev_handle_free(
			 &handle,
			 NULL );
		}
	}
	else
	{
		SMDEV_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		SMDEV_TEST_ASSERT_IS_NULL(
		 "handle",
		 handle );

		SMDEV_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_SMDEV_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libsmdev_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libsmdev_handle_free function
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libsmdev_handle_free(
	          NULL,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libsmdev_handle_open functions
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libsmdev_handle_t *handle      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = smdev_test_handle_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libsmdev_handle_initialize(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libsmdev_handle_open(
	          handle,
	          narrow_source,
	          LIBSMDEV_OPEN_READ,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libsmdev_handle_close(
	          handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libsmdev_handle_free(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libsmdev_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libsmdev_handle_open_wide functions
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libsmdev_handle_t *handle      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = smdev_test_handle_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libsmdev_handle_initialize(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libsmdev_handle_open_wide(
	          handle,
	          wide_source,
	          LIBSMDEV_OPEN_READ,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libsmdev_handle_close(
	          handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libsmdev_handle_free(
	          &handle,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libsmdev_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libsmdev_handle_get_number_of_sessions functions
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_get_number_of_sessions(
     libsmdev_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_sessions    = 0;
	int result               = 0;

	result = libsmdev_handle_get_number_of_sessions(
	          handle,
	          &number_of_sessions,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libsmdev_handle_get_number_of_sessions(
	          NULL,
	          &number_of_sessions,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libsmdev_handle_get_number_of_sessions(
	          handle,
	          NULL,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libsmdev_handle_get_number_of_tracks functions
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_get_number_of_tracks(
     libsmdev_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_tracks    = 0;
	int result               = 0;

	result = libsmdev_handle_get_number_of_tracks(
	          handle,
	          &number_of_tracks,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libsmdev_handle_get_number_of_tracks(
	          NULL,
	          &number_of_tracks,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libsmdev_handle_get_number_of_tracks(
	          handle,
	          NULL,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libsmdev_handle_get_number_of_error_retries functions
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_get_number_of_error_retries(
     libsmdev_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_error_retries    = 0;
	int result               = 0;

	result = libsmdev_handle_get_number_of_error_retries(
	          handle,
	          &number_of_error_retries,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libsmdev_handle_get_number_of_error_retries(
	          NULL,
	          &number_of_error_retries,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libsmdev_handle_get_number_of_error_retries(
	          handle,
	          NULL,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libsmdev_handle_get_number_of_errors functions
 * Returns 1 if successful or 0 if not
 */
int smdev_test_handle_get_number_of_errors(
     libsmdev_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_errors    = 0;
	int result               = 0;

	result = libsmdev_handle_get_number_of_errors(
	          handle,
	          &number_of_errors,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        SMDEV_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libsmdev_handle_get_number_of_errors(
	          NULL,
	          &number_of_errors,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libsmdev_handle_get_number_of_errors(
	          handle,
	          NULL,
	          &error );

	SMDEV_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        SMDEV_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	libsmdev_handle_t *handle        = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( SMDEV_TEST_HANDLE_VERBOSE )
	libsmdev_notify_set_verbose(
	 1 );
	libsmdev_notify_set_stream(
	 stderr,
	 NULL );
#endif

	SMDEV_TEST_RUN(
	 "libsmdev_handle_initialize",
	 smdev_test_handle_initialize );

	SMDEV_TEST_RUN(
	 "libsmdev_handle_free",
	 smdev_test_handle_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		SMDEV_TEST_RUN_WITH_ARGS(
		 "libsmdev_handle_open",
		 smdev_test_handle_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		SMDEV_TEST_RUN_WITH_ARGS(
		 "libsmdev_handle_open_wide",
		 smdev_test_handle_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBSMDEV_HAVE_BFIO )

		/* TODO add test for libsmdev_handle_open_file_io_handle */

#endif /* defined( LIBSMDEV_HAVE_BFIO ) */

		/* TODO add test for libsmdev_handle_close */

		/* Initialize test
		 */
		result = smdev_test_handle_open_source(
		          &handle,
		          source,
		          &error );

		SMDEV_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        SMDEV_TEST_ASSERT_IS_NOT_NULL(
	         "handle",
	         handle );

	        SMDEV_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		SMDEV_TEST_RUN_WITH_ARGS(
		 "libsmdev_handle_get_number_of_sessions",
		 smdev_test_handle_get_number_of_sessions,
		 handle );

		SMDEV_TEST_RUN_WITH_ARGS(
		 "libsmdev_handle_get_number_of_tracks",
		 smdev_test_handle_get_number_of_tracks,
		 handle );

		SMDEV_TEST_RUN_WITH_ARGS(
		 "libsmdev_handle_get_number_of_error_retries",
		 smdev_test_handle_get_number_of_error_retries,
		 handle );

		SMDEV_TEST_RUN_WITH_ARGS(
		 "libsmdev_handle_get_number_of_errors",
		 smdev_test_handle_get_number_of_errors,
		 handle );

		/* Clean up
		 */
		result = smdev_test_handle_close_source(
		          &handle,
		          &error );

		SMDEV_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		SMDEV_TEST_ASSERT_IS_NULL(
	         "handle",
	         handle );

	        SMDEV_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		smdev_test_handle_close_source(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}


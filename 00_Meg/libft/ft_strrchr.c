/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:39:08 by menwu             #+#    #+#             */
/*   Updated: 2024/10/09 18:01:40 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen((char *)str);
	if ((char)c == '\0')
		return ((char *)&str[len]);
	while (len--)
	{
		if (str[len] == (char)c)
			return ((char *) &str[len]);
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	x[] = "Is os delicioso";
	char	*y;

	printf("The expected result: %p", strrchr(x, 'o'));
	y = ft_strrchr(x, 'o');
	printf("\nOur result is: %p", y);

	return (0);
}
*/

/*
#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[] = "Hello, World!";
    char str2[] = "ABCDABCDABCD";
    char str3[] = "";
    char str4[] = "Test with null terminator\0hidden text";
    
    // Test 1: Find 'o' in "Hello, World!"
    printf("Test 1: Find 'o' in \"%s\"\n", str1);
    printf("Expected: %p\n", strrchr(str1, 'o'));
    printf("Result:   %p\n", strrchr(str1, 'o'));
    printf("Remaining string from last 'o': %s\n\n", strrchr(str1, 'o'));

    // Test 2: Find 'A' in "ABCDABCDABCD" (Multiple 'A's)
    printf("Test 2: Find 'A' in \"%s\"\n", str2);
    printf("Expected: %p\n", strrchr(str2, 'A'));
    printf("Result:   %p\n", strrchr(str2, 'A'));
    printf("Remaining string from last 'A': %s\n\n", strrchr(str2, 'A'));

    // Test 3: Character not in the string ('X' in "ABCDABCDABCD")
    printf("Test 3: Find 'X' in \"%s\"\n", str2);
    printf("Expected: (null)\n");
    printf("Result:   %p\n\n", strrchr(str2, 'X'));

    // Test 4: Search for the null terminator '\0'
    printf("Test 4: Find '\\0' in \"%s\"\n", str1);
    printf("Expected: %p\n", strrchr(str1, '\0'));
    printf("Result:   %p\n", strrchr(str1, '\0'));
    printf("Remaining string from '\\0': \"%s\"\n\n", strrchr(str1, '\0'));

    // Test 5: Empty string (search any character in "")
    printf("Test 5: Find 'A' in an empty string \"%s\"\n", str3);
    printf("Expected: (null)\n");
    printf("Result:   %p\n\n", strrchr(str3, 'A'));

    // Test 6: String with embedded null terminator
    printf("Test 6: Find 't' in a string with embedded '\\0': 
								\"%s\\0hidden text\"\n", str4);
    printf("Expected: %p\n", strrchr(str4, 't'));
    printf("Result:   %p\n", strrchr(str4, 't'));
    printf("Remaining string from last 't': %s\n\n", strrchr(str4, 't'));

    // Test 7: Find the first character in a string
    printf("Test 7: Find 'H' in \"%s\"\n", str1);
    printf("Expected: %p\n", strrchr(str1, 'H'));
    printf("Result:   %p\n", strrchr(str1, 'H'));
    printf("Remaining string from last 'H': %s\n\n", strrchr(str1, 'H'));

    return 0;
}
*/

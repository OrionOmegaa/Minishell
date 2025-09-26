/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: refactor <refactor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:30:00 by refactor          #+#    #+#             */
/*   Updated: 2025/09/26 17:30:00 by refactor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	printf("ascii: %d\n", '\'');
	return (0);
}

/*int main() {
	char buffer[1024];
	int count = 0;

	while (1) {
		printf("Test %d - avant lecture\n", ++count);
		fflush(stdout);

		if (!fgets(buffer, sizeof(buffer), stdin))
			break ;

		printf("Reçu: %s", buffer);
	}
	return (0);
}*/

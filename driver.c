#include <stdio.h>
#include <string.h>
#include "user.h"


int main(void) {
	struct User * head=NULL;
	head = add(head, "rob");
	head = add(head, "hanif");
	head = add(head, "gahyun");
	head = add(head, "matt");
	head = add(head, "sumita");
	head = add(head, "james");

	printLog(head); //confirms that all users are actually there and the linked list can be traversed

	struct Digest testDigest;
	generateDigest(&testDigest, head->next);

	printf("\nHash stored in james: ");
	printDigest(head->hash);

	printf("Hash calculated from sumita: ");
	printDigest(testDigest);

	if (digest_equal(head->hash, testDigest)) {
		printf("Hash relationship test PASSED\n\n");
	}
	else {
		printf("Hash relationship test FAILED\n\n");
	}


	// strcpy(head->next->Username, "changed");
	// printf("\nChanged sumita's username to: %s\n\n", head->next->Username);

	head->next->loginTime += 1000;
	printf("\nChanged sumita's login timestamp.\n\n");

	// head->hash.hash0 += 1;
	// printf("\nChanged james's stored hash.\n\n");

	// strcpy(head->next->Username, "brokenlink");
	// printf("\nChanged sumita after james's hash was created.\n\n");

	verify(head);
}
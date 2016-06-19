#include <r_util.h>
#include "minunit.h"

bool test_r_queue_add_remove(void) {
	int i, j;
	// Create queue with max size 5.
	RQueue* queue = r_queue_new (5);
	for (i = 0; i < 5; ++i) {
		mu_assert ("enqueue to available slot",
				r_queue_enqueue (queue, (void*)(intptr_t)((i + 1) * 10)));
	}
	mu_assert_eq (queue->capacity, 5, "original capacity is 5");
	mu_assert ("enqueue but it's full! Increase Capacity!",
				r_queue_enqueue (queue, (void*)(intptr_t)60));
	mu_assert_eq (queue->capacity, 10, "new capacity should be double old");
	for (i = 0; i < 6; ++i) {
		j = (int)(intptr_t)r_queue_dequeue (queue);
		mu_assert_eq (j, (i + 1) * 10, "front item from queue");
	}
	j = (int)(intptr_t)r_queue_dequeue (queue);
	mu_assert_eq (j, (int)(intptr_t)NULL, "Empty queue dequeue.");
	mu_end;
}

int all_tests() {
	mu_run_test(test_r_queue_add_remove);
	return tests_passed != tests_run;
}

int main(int argc, char **argv) {
	return all_tests();
}
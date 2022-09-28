// cpp-version
#include <iostream>
#include <random>
#include <set>

// c-version
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// cpp-version
void lottery_cpp();
void lottery_cpp2();
// c-version
void lottery_c();
void quicksort_c(int *data, int count);

int main(int argc, const char *argv[]) {
	// Test it!
	lottery_cpp();
	lottery_cpp2();
	//lottery_c();
	
	return 0;
}

void lottery_cpp() {
	// Using-Direktiven
	using std::cout; using std::endl;
	using std::size_t; using std::set; using std::less;
	using std::mt19937;	using std::random_device;
	using std::uniform_int_distribution;
	
	// Einstellung für 7 aus 49
	constexpr size_t lottery_numbers_to_draw = 5;
	constexpr size_t lottery_numbers_range_min = 1;
	constexpr size_t lottery_numbers_range_max = 50;
	
	// Ein std::set<T> mit der Sortierung std::less<T> und T = std::size_t für
	// die Lottozahlen.
	set<size_t, less<size_t>> lottery_numbers;
	
	// Ein simpler Zufallsgenerator für Integer-Werte im gewählten Wertebereich
	// und ein Lambda-Ausdruck, der einen solchen Wert berechnet.
	mt19937 random_generator({ random_device()() });
	uniform_int_distribution<> lottery_distribution(lottery_numbers_range_min,
													lottery_numbers_range_max);
	auto draw_lottery_number = [&random_generator, &lottery_distribution] {
		return lottery_distribution(random_generator);
	};
	
	// Wir fügen solange zufällige Werte hinzu, bis wir die gewollte Anzahl an
	// Werten im std::set lottery_numbers haben. std::set().insert().second ist
	// true, wenn der Wert erfolgreich eingefügt wurde.
	for (size_t draw_count = 0;
		 draw_count < lottery_numbers_to_draw;
		 ++draw_count) {
		while (!lottery_numbers.insert(draw_lottery_number()).second) {
		}
	}
		
	// Gibt die Lottozahlen auf der Konsole aus
	for (auto n: lottery_numbers) {
		cout << n << ' ';
	}
	cout << endl;
}



void lottery_cpp2() {
	// Using-Direktiven
	using std::cout; using std::endl;
	using std::size_t; using std::set; using std::less;
	using std::mt19937;	using std::random_device;
	using std::uniform_int_distribution;
	
	// Einstellung für 7 aus 49
	constexpr size_t lottery_numbers_to_draw = 2;
	constexpr size_t lottery_numbers_range_min = 1;
	constexpr size_t lottery_numbers_range_max = 12;
	
	// Ein std::set<T> mit der Sortierung std::less<T> und T = std::size_t für
	// die Lottozahlen.
	set<size_t, less<size_t>> lottery_numbers;
	
	// Ein simpler Zufallsgenerator für Integer-Werte im gewählten Wertebereich
	// und ein Lambda-Ausdruck, der einen solchen Wert berechnet.
	mt19937 random_generator({ random_device()() });
	uniform_int_distribution<> lottery_distribution(lottery_numbers_range_min,
													lottery_numbers_range_max);
	auto draw_lottery_number = [&random_generator, &lottery_distribution] {
		return lottery_distribution(random_generator);
	};
	
	// Wir fügen solange zufällige Werte hinzu, bis wir die gewollte Anzahl an
	// Werten im std::set lottery_numbers haben. std::set().insert().second ist
	// true, wenn der Wert erfolgreich eingefügt wurde.
	for (size_t draw_count = 0;
		 draw_count < lottery_numbers_to_draw;
		 ++draw_count) {
		while (!lottery_numbers.insert(draw_lottery_number()).second) {
		}
	}
		
	// Gibt die Lottozahlen auf der Konsole aus
	for (auto n: lottery_numbers) {
		cout << n << ' ';
	}
	cout << endl;
}


void lottery_c() {
	// Initialisierung von rand()
	srand((unsigned)time(0));
	
	// Array, in dem die Zahlen gespeichert und dann "In-Place" sortiert werden
	int lottery_numbers[7];
	
	// Berechnet zufällige Werte zwischen aus [1,49], wenn diese noch nicht in
	// lottery_numbers vorhanden sind, werden sie hinzugefügt.
	// Am Ende der Schleife ist garantiert, dass lottery_numbers 7 verschiedene
	// Elemente enthält.
	for (int draw_count = 0; draw_count < 7; ++draw_count) {
		bool already_drawn;
		int drawn_number;
		do {
			already_drawn = false;
			drawn_number = rand() % 49 + 1;
			for (int i = 0; i < 7; ++i) {
				if (lottery_numbers[i] == drawn_number) {
					already_drawn = true;
					break;
				}
			}
		} while (already_drawn == true);
		
		lottery_numbers[draw_count] = drawn_number;
	}
	
	// Sortiert die 7 Werte in lottery_numbers aufsteigend mit einem
	// "In-Place"-Quicksort Verfahren (Implementation siehe unten)
	quicksort_c(lottery_numbers, 7);
	
	// Gibt die Lottozahlen auf der Konsole aus
	for (int i = 0; i < 7; ++i) {
		printf("%d ", lottery_numbers[i]);
	}
	printf("\n");
}

// In-Place-Quicksort, rekursiv
// Funktionsweise: http://en.wikipedia.org/wiki/Quicksort
void quicksort_c(int *data, int count) {
    if (count < 2) {
        return;
	}
	
    int pivot = data[count / 2];
	
    int *left = data;
    int *right = data + count - 1;

    while (left <= right) {
        if (*left < pivot) {
            left++;
            continue;
        }
        
		if (*right > pivot) {
            right--;
            continue;
        }
		
        int temp = *left;
        *left++ = *right;
        *right-- = temp;
    }
	
    quicksort_c(data, (int)(right - data + 1));
    quicksort_c(left, (int)(data + count - left));
}

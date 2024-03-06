#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PRODUCER_COUNT 10
#define CONSUMER_COUNT 5
#define BUFFER_SIZE 100

typedef struct {
    char name[50];
    int salary;
    char dob[11];
} Person;

typedef struct node {
    Person data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Buffer;

Buffer buffer;

int nth_birthday;
char birthday_month[3];
int found;

int month_count[12];
int total_salary;
int num_consumers;


// Function prototypes
void* producer_thread(void* arg);
void* consumer_thread(void* arg);
void add_to_buffer(Person data);
Person remove_from_buffer();
void print_results();


int main(int argc, char** argv) {
    // Check command line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s n DD-MM database\n", argv[0]);
        return 1;
    }

    // Initialize global variables
    buffer.head = NULL;
    buffer.tail = NULL;
    buffer.size = 0;
    pthread_mutex_init(&buffer.lock, NULL);
    pthread_cond_init(&buffer.cond, NULL);
    num_producers = PRODUCER_COUNT;
    num_consumers = CONSUMER_COUNT;
    found = 0;
    total_salary = 0;
    memset(month_count, 0, sizeof(month_count));
    search_n = atoi(argv[1]);
    sscanf(argv[2], "%d-%d", &search_day, &search_month);
    search_month--; // Adjust for zero-based array indexing

    // Create producer and consumer threads
    pthread_t producers[PRODUCER_COUNT];
    pthread_t consumers[CONSUMER_COUNT];
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_create(&producers[i], NULL, producer_thread, argv[3]);
    }
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_create(&consumers[i], NULL, consumer_thread, NULL);
    }

    // Wait for threads to finish
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Print results and clean up
    print_results();
    pthread_mutex_destroy(&buffer.lock);
    pthread_cond_destroy(&buffer.cond);

    return 0;
}

void* producer_thread(void* arg) {
    char* database_name = (char*)arg;

    // Open database file
    FILE* file = fopen(database_name, "r");
    if (file == NULL) {
        perror("Error opening database file");
        return NULL;
    }

    // Read entries from file and add to buffer
    Person person;
    while (fscanf(file, "%s %d %d-%d-%d", person.name, &person.salary, &person.day, &person.month, &person.year) == 5) {
        pthread_mutex_lock(&buffer.lock);
        while (buffer.size == BUFFER_SIZE) {
            pthread_cond_wait(&buffer.cond, &buffer.lock);
        }
        add_to_buffer(person);
        pthread_cond_signal(&buffer.cond);
        pthread_mutex_unlock(&buffer.lock);
    }

    // Close file and decrement number of producers
    fclose(file);
    pthread_mutex_lock(&buffer.lock);
    num_producers--;
    pthread_cond_signal(&buffer.cond);
    pthread_mutex_unlock(&buffer.lock);

    return NULL;
}

void* consumer_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&buffer.lock);
        while (buffer.size == 0 && num_producers > 0) {
            pthread_cond_wait(&buffer.cond, &buffer.lock);
        }
        if (buffer.size == 0 && num_producers == 0) {
            pthread_mutex_unlock(&buffer.lock);
            break;
        }
        Person person = remove_from_buffer();
        pthread_cond_signal(&buffer.cond);
        pthread_mutex_unlock(&buffer.lock);

        // Process entry
        total_salary += person.salary;
        month_count[person.month - 1]++;
        if (found == 0 && person.year + search_n == 2022 && person.month == search_month && person.day == search_day) {
            found = 1;
            pthread_mutex_lock(&buffer.lock);
            pthread_cond_broadcast(&buffer.cond);
            pthread_mutex_unlock(&buffer.lock);
            break;
        }
    }

    return NULL;
}

void add_to_buffer(Person data) {
    // Create new node and copy data
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    // Add node to end of list
    if (buffer.tail == NULL) {
        buffer.head = node;
        buffer.tail = node;
    } else {
        buffer.tail->next = node;
        node->prev = buffer.tail;
        buffer.tail = node;
    }

    buffer.size++;
}

Person remove_from_buffer() {
    // Remove first node from list
    Node* node = buffer.head;
    Person data = node->data;
    buffer.head = node->next;
    if (buffer.head == NULL) {
        buffer.tail = NULL;
    } else {
        buffer.head->prev = NULL;
    }
    free(node);

    buffer.size--;

    return data;
}

void print_results() {
    if (found) {
        printf("#Average salary: %d\n", total_salary / num_consumers);
        printf("#Month histogram:\n");
        printf("+-----+-----+------+-----+-----+-----+-----+-----+-----+-------+-----+-----+\n");
        printf("| Jan | Feb |  Mar | Apr | May | Jun | Jul | Aug | Sep |  Oct  | Nov | Dec |\n");
        printf("+-----+-----+------+-----+-----+-----+-----+-----+-----+-------+-----+-----+\n");
        for (int i = 0; i < 12; i++) {
            printf("| %3d ", month_count[i]);
        }
        printf("|\n+-----+-----+------+-----+-----+-----+-----+-----+-----+-------+-----+-----+\n");
    } else {
        fprintf(stderr, "No entries found!\n");
    }
}

/*
void* _function(void* arg) {
  int id = (int)arg;  // The id of this consumer thread
  int entry;  // The entry being processed
  int salary;  // The salary from the entry
  int month;  // The month of birth from the entry
  int day;  // The day of birth from the entry
  int age;  // The age of the person in the entry

  // Process entries from the buffer
  while (1) {
    // Get an entry from the buffer
    pthread_mutex_lock(&buffer_mutex);
    while (buffer_count == 0 && producers_finished < PRODUCER_COUNT) {
      pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
    }
    if (buffer_count == 0 && producers_finished == PRODUCER_COUNT) {
      pthread_mutex_unlock(&buffer_mutex);
      break;
    }
    entry = buffer[buffer_start];
    buffer_count--;
    buffer_start = (buffer_start + 1) % BUFFER_SIZE;
    pthread_cond_signal(&buffer_not_full);
    pthread_mutex_unlock(&buffer_mutex);

    // Extract the salary and date of birth from the entry
    salary = entry >> 16;
    month = (entry >> 8) & 0xff;
    day = entry & 0xff;

    // Calculate the age of the person in this entry
    age = nth_birthday - (2022 - (month < 3 ? 2021 : 2020));

    // Check if this is the sought entry
    if (age == nth_birthday && month == search_month && day == search_day) {
      // Found the sought entry, so mark it as found and signal the other threads to stop
      pthread_mutex_lock(&buffer_mutex);
      found_entry = strdup(line);
      entry_found = 1;
      pthread_cond_broadcast(&buffer_not_empty);
      pthread_cond_broadcast(&buffer_not_full);
      pthread_mutex_unlock(&buffer_mutex);
      break;
    }

    // Update the statistics for this entry
    total_salary += salary;
    month_count[month - 1]++;
  }

  return NULL;
}


void* producer_function(void* arg) {
  int id = (int)arg;  // The id of this producer thread
  char filename[20];  // The name of the file to read
  FILE* file;  // The file pointer
  char line[100];  // The line being read from the file
  int salary;  // The salary from the line
  int year, month, day;  // The date of birth from the line
  int entry;  // The entry to add to the buffer

  // Open the file for this producer
  sprintf(filename, "db%d.txt", id);
  file = fopen(filename, "r");
  if (file == NULL) {
    perror("fopen");
    return NULL;
  }

  // Read lines from the file and add them to the buffer
  while (fgets(line, sizeof(line), file) != NULL) {
    // Parse the line to get the salary and date of birth
    if (sscanf(line, "%d %d-%d-%d", &salary, &year, &month, &day) != 4) {
      fprintf(stderr, "Error parsing line: %s", line);
      continue;
    }

    // Create the entry to add to the buffer
    entry = (salary << 16) | (month << 8) | day;

  / Add the entry to the buffer
    pthread_mutex_lock(&buffer_mutex);
    while (buffer_count == BUFFER_SIZE) {
      pthread_cond_wait(&buffer_not_full, &buffer_mutex);
    }
    buffer[buffer_end] = entry;
    buffer_count++;
    buffer_end = (buffer_end + 1) % BUFFER_SIZE;
    pthread_cond_signal(&buffer_not_empty);
    pthread_mutex_unlock(&buffer_mutex);
  }

  // Close the file and mark this producer as finished
  fclose(file);
  pthread_mutex_lock(&buffer_mutex);
  producers_finished++;
  pthread_mutex_unlock(&buffer_mutex);

  return NULL;


  void* producer_function(void* arg) {
  char* entry;

  while (1) {
    // Read an entry from the database
    entry = read_database_entry();
    if (entry == NULL) {
      break;  // No more entries to read
    }

    // Wait until there is space in the buffer
    pthread_mutex_lock(&buffer_mutex);
    while (buffer_count == BUFFER_SIZE) {
      pthread_cond_wait(&buffer_full_cond, &buffer_mutex);
    }

    // Add the entry to the buffer
    buffer[buffer_tail] = entry;
    buffer_tail = (buffer_tail + 1) % BUFFER_SIZE;
    buffer_count++;

    // Signal that there is a new entry in the buffer
    pthread_cond_signal(&buffer_empty_cond);
    pthread_mutex_unlock(&buffer_mutex);
  }

  // Signal that there are no more entries to read
  pthread_mutex_lock(&buffer_mutex);
  producers_finished = 1;
  pthread_cond_broadcast(&buffer_empty_cond);
  pthread_mutex_unlock(&buffer_mutex);

  return NULL;
}

}*/
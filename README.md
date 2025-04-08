# ft_irc

**ft_irc** is a fully functional IRC (Internet Relay Chat) server written in **C++98**. It follows the IRC protocol to allow multiple clients to connect, authenticate, join channels, and communicate in real-time. This project was developed as an educational exercise to understand low-level networking and concurrent client handling using non-blocking sockets.

## 💡 Overview

- 🧠 Written in **C++98**
- 🔗 Handles **multiple simultaneous clients**
- 🛑 Uses **non-blocking I/O with `poll()`**
- 🗣️ Compatible with real IRC clients like **HexChat**
- ⚙️ No multithreading or forking
- 🔐 Clients must authenticate with a password

## 🧰 Features

- IRC server executable: `ircserv`
- TCP communication over IPv4/IPv6
- Supports essential IRC commands:
  - `PASS`, `NICK`, `USER`
  - `JOIN`, `PRIVMSG`, `QUIT`
  - `KICK`, `INVITE`, `TOPIC`, `MODE`
- Channel support with:
  - Operator roles
  - Invitation-only mode
  - Password-protected channels
  - User limit per channel
- Clean error handling and resilience to partial input
- Configuration through command-line arguments

### Prerequisites

- C++98-compatible compiler
- `make` utility
- IRC client (e.g. [HexChat](https://hexchat.github.io/))

### Build

```bash
make

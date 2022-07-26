#!/bin/bash
toxiproxy-cli toxic add aby3_party_1 -n mytoxydown  -t latency -a latency=1000 --downstream
toxiproxy-cli toxic add aby3_party_1 -n mytoxyup -t latency -a latency=1000 --upstream

toxiproxy-cli toxic add aby3_party_2 -n mytoxydown  -t latency -a latency=1000 --downstream
toxiproxy-cli toxic add aby3_party_2 -n mytoxyup -t latency -a latency=1000 --upstream

toxiproxy-cli toxic add aby3_party_3 -n mytoxydown  -t latency -a latency=1000 --downstream
toxiproxy-cli toxic add aby3_party_3 -n mytoxyup -t latency -a latency=1000 --upstream

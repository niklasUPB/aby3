toxiproxy-cli create Conclave1 --listen 127.0.0.1:50010 --upstream 127.0.0.1:50001
toxiproxy-cli create Conclave2 --listen 127.0.0.1:50020 --upstream 127.0.0.1:50002
toxiproxy-cli create Conclave3 --listen 127.0.0.1:50030 --upstream 127.0.0.1:50003
toxiproxy-cli toxic add Conclave1 -t latency -n latency_upstream -a latency=100 --upstream
toxiproxy-cli toxic add Conclave1 -t latency -n latency_downstream -a latency=100 --downstream
toxiproxy-cli toxic add Conclave1 -t bandwidth -n bandwidth_upstream -a rate=10000 --upstream
toxiproxy-cli toxic add Conclave1 -t bandwidth -n bandwidth_downstream -a rate=10000 --downstream
toxiproxy-cli toxic add Conclave2 -t latency -n latency_upstream -a latency=100 --upstream
toxiproxy-cli toxic add Conclave2 -t latency -n latency_downstream -a latency=100 --downstream
toxiproxy-cli toxic add Conclave2 -t bandwidth -n bandwidth_upstream -a rate=10000 --upstream
toxiproxy-cli toxic add Conclave2 -t bandwidth -n bandwidth_downstream -a rate=10000 --downstream
toxiproxy-cli toxic add Conclave3 -t latency -n latency_upstream -a latency=100 --upstream
toxiproxy-cli toxic add Conclave3 -t latency -n latency_downstream -a latency=100 --downstream
toxiproxy-cli toxic add Conclave3 -t bandwidth -n bandwidth_upstream -a rate=10000 --upstream
toxiproxy-cli toxic add Conclave3 -t bandwidth -n bandwidth_downstream -a rate=10000 --downstream

# 1. Aşama: Derleme aşaması (Build Stage)
FROM gcc:latest AS builder
WORKDIR /app
COPY . /app
RUN make test-build

# 2. Aşama: Çalıştırma aşaması (Runtime Stage)
FROM debian:stable-slim
RUN apt-get update && apt-get install -y make && apt-get clean && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY --from=builder /app/bin /app/bin
COPY --from=builder /app/Makefile .
ENTRYPOINT ["make"]
CMD ["test-run"]

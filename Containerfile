FROM alpine

COPY . .

WORKDIR /build

RUN rm -r *

RUN apk add --no-cache g++ cmake make

RUN cmake ..

RUN make



CMD ["./main"]


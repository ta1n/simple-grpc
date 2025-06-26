FROM python:3.10-slim

WORKDIR /app

COPY . .
RUN pip install --no-cache-dir -r requirements.txt grpcio-tools

# Copy proto files and client code
# COPY ./proto ./proto
# COPY ./client.py .

# RUN python -m grpc_tools.protoc -I./proto --python_out=. --grpc_python_out=. ./proto/myservice.proto

CMD ["python", "client.py"]

#!/usr/bin/env bash
set -euo pipefail

IMAGE_NAME="dev-env-gsisi"
CONTAINER_NAME="dev-env-creo-container"
CONTAINER_ENTRY="/bin/bash"
WORK_DIR="/home/dev/creo"
DOCKERFILE="Docker File"
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

container_stop() {
    if docker container inspect "$CONTAINER_NAME" >/dev/null 2>&1; then
        docker stop "$CONTAINER_NAME" >/dev/null
        echo ">> stopped container: $CONTAINER_NAME"
    else
        echo ">> container does not exist: $CONTAINER_NAME"
    fi
}

container_start() {
    if docker container inspect "$CONTAINER_NAME" >/dev/null 2>&1; then
        local running
        running="$(docker inspect --format '{{.State.Running}}' "$CONTAINER_NAME")"
        if [[ "$running" == "true" ]]; then
            docker exec -it "$CONTAINER_NAME" "$CONTAINER_ENTRY"
        else
            docker start -ai "$CONTAINER_NAME"
        fi
    else
        echo ">> creating development container"
        docker run -it \
            --name "$CONTAINER_NAME" \
            --hostname dev \
            --cap-add=SYS_PTRACE \
            --security-opt seccomp=unconfined \
            --mount "type=bind,source=$PROJECT_ROOT,target=$WORK_DIR" \
            --workdir "$WORK_DIR" \
            "$IMAGE_NAME" "$CONTAINER_ENTRY"
    fi
}

image_build() {
    echo ">> building image: $IMAGE_NAME"
    docker build --platform linux/amd64 -f "$PROJECT_ROOT/$DOCKERFILE" \
        -t "$IMAGE_NAME" "$PROJECT_ROOT"
}

clean() {
    if docker container inspect "$CONTAINER_NAME" >/dev/null 2>&1; then
        docker rm -f "$CONTAINER_NAME"
    fi
    if docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
        docker image rm "$IMAGE_NAME"
    fi
}

print_usage() {
    echo "Usage: $0 {container-start|container-stop|image-build|clean}"
}

main() {
    if ! command -v docker >/dev/null 2>&1; then
        echo "Docker was not found. Install and start Docker Desktop, then retry." >&2
        exit 1
    fi
    if ! docker info >/dev/null 2>&1; then
        echo "Docker is installed but its daemon is unavailable. Start Docker Desktop, then retry." >&2
        exit 1
    fi

    case "${1:-}" in
        container-start) container_start ;;
        container-stop)  container_stop ;;
        image-build)     image_build ;;
        clean)            clean ;;
        *)                print_usage; exit 2 ;;
    esac
}

main "$@"

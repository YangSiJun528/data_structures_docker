# Docker + Dev Container 기반 C 개발 환경 가이드

이 저장소는 이제 **JetBrains Dev Containers 예제**와 **CLion Dev Container 문서** 흐름에 맞춰, **CLion에서 바로 열 수 있는 Dev Container 환경**을 기본값으로 사용합니다.

- 참고 예제: https://github.com/JetBrains/devcontainers-examples
- CLion 문서: https://www.jetbrains.com/help/clion/start-dev-container-inside-ide.html
## 1. 무엇이 달라졌나요?

- `.devcontainer/devcontainer.json`
  - `customizations.jetbrains.backend`를 `CLion`으로 지정했습니다.
  - VSCode 전용 설정은 제거하고 JetBrains 기준 설정만 남겼습니다.
- `.devcontainer/Dockerfile`
  - C 개발 도구(`gcc`, `gdb`, `cmake`, `make`, `valgrind`)와 함께 JetBrains 원격 백엔드가 안정적으로 뜨는 데 필요한 패키지(`curl`, `unzip`, `procps`, X 관련 라이브러리)를 포함했습니다.
- `CMakeLists.txt`
  - `Data-Structures` 아래의 모든 `.c` 파일을 CLion에서 개별 실행 타깃으로 인식하도록 추가했습니다.
  - 예를 들어 `Data-Structures/Linked_List/Q1_A_LL.c`는 `Linked_List_Q1_A_LL` 타깃으로 보입니다.
- 기존 `.vscode`
  - VSCode 전용 `tasks.json`, `launch.json`은 삭제했습니다.
  - 해당 역할은 CLion의 CMake 타깃과 Run/Debug 구성이 대신합니다.

## 2. 준비물

1. Docker Desktop 설치
   - https://www.docker.com/products/docker-desktop
2. CLion 설치
3. CLion의 `Dev Containers` 플러그인 설치
   - `Settings/Preferences > Plugins > Marketplace > Dev Containers`

## 3. 프로젝트 받기

```bash
git clone --depth=1 https://github.com/krafton-jungle/data_structures_docker.git
cd data_structures_docker
```

## 4. CLion에서 Dev Container로 열기

1. CLion에서 이 프로젝트 폴더를 엽니다.
2. `.devcontainer/devcontainer.json` 파일을 엽니다.
3. 왼쪽 거터의 컨테이너 아이콘을 눌러 `Create Dev Container and Mount Sources`를 실행합니다.
4. 백엔드 IDE로 `CLion`을 선택합니다.
5. 컨테이너 빌드가 끝나면 `Connect`를 눌러 접속합니다.

JetBrains 문서 기준으로, CLion은 `.devcontainer/devcontainer.json`이 있는 프로젝트를 직접 열고 컨테이너를 생성할 수 있습니다. 이 저장소는 그 흐름에 맞게 맞춰져 있습니다.

## 5. CLion에서 빌드와 디버깅

이 저장소는 원래 단일 C 파일 묶음 중심이라 CLion이 프로젝트로 인식하기 어려웠습니다. 이를 위해 루트 `CMakeLists.txt`를 추가했습니다.

- `Data-Structures` 아래의 각 `.c` 파일이 CMake 실행 타깃으로 자동 생성됩니다.
- CLion 오른쪽 상단 실행 구성에서 원하는 타깃을 선택한 뒤 실행하거나 디버깅하면 됩니다.
- 디버깅은 컨테이너 안의 `gdb`를 사용합니다.
- 각 문제 파일은 `main`을 포함한 **독립 실행 파일**로 취급합니다. 여러 `.c` 파일을 하나의 실행 파일로 합치지 않습니다.

실행할 때는 CLion의 **`CMake Application` 타깃**을 사용하세요.

- `.idea/runConfigurations/`에는 공유용 CMake 실행 구성이 포함되어 있습니다.
- `Current File` 또는 `C/C++ File` 실행은 현재 파일을 직접 컴파일하므로 사용하지 않는 편이 좋습니다.
- CMake 타깃으로 실행하면 바이너리는 `cmake-build-*/bin` 아래에 생성됩니다.

기존 `.vscode` 설정과의 대응 관계는 아래와 같습니다.

- `tasks.json`
  - `/usr/bin/gcc -g ${file}`로 현재 파일 하나를 빌드하던 설정이었습니다.
  - CLion에서는 각 `.c` 파일이 CMake 실행 타깃이 되므로, 별도 VSCode task 없이 같은 목적을 달성합니다.
- `launch.json`
  - 방금 빌드한 실행 파일을 `gdb`로 디버깅하던 설정이었습니다.
  - CLion에서는 생성된 타깃을 Run/Debug 하면 컨테이너 안의 `gdb`를 사용합니다.

즉, `.vscode`에 있던 내용 중 Dev Container 자체에 직접 옮길 수 있는 값은 거의 없었고, 실제 의미 있는 부분은 이미 다음 형태로 반영되어 있습니다.

- 컴파일러: 컨테이너에 `gcc` 설치
- 디버거: 컨테이너에 `gdb` 설치
- 빌드 진입점: 루트 `CMakeLists.txt`
- 실행 단위: 각 문제 파일별 실행 타깃

예시 타깃 이름:

- `Linked_List_Q1_A_LL`
- `Stack_and_Queue_Q4_C_SQ`
- `Binary_Tree_Q2_E_BT`
- `Binary_Search_Tree_Q5_F_BST`

## 6. 폴더 구조

```text
data_structures_docker/
├── .devcontainer/
│   ├── devcontainer.json
│   └── Dockerfile
├── CMakeLists.txt
├── Data-Structures/
│   ├── Binary_Search_Tree/
│   ├── Binary_Tree/
│   ├── Linked_List/
│   └── Stack_and_Queue/
└── README.md
```

## 7. 학습 순서

권장 순서는 기존과 동일합니다.

`Linked List -> Stack and Queue -> Binary Tree -> Binary Search Tree`

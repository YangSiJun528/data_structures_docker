# CZ1007 Data Structures 과제 1차 평가

## 개요
- 대상: `Data-Structures` 폴더의 과제 풀이 코드
- 범위: 각 문제에서 직접 구현해야 하는 함수와, 그 함수를 위해 학생이 추가한 보조 함수
- 제외: `main`, 입출력 메뉴 루프, 기본 제공 ADT 연산(`push/pop/enqueue/dequeue/findNode/insertNode/removeNode/removeAll` 등), 과제 평가와 무관한 제공 프레임 이슈, 실제 호출되지 않는 제공 스텁
- 단, `main`이나 바깥 호출부가 실제로 메모리 해제나 상태 정리를 해 주는 경우에는 그 처리를 평가에 반영했다. 외부가 커버하지 못하는 함수 내부 문제만 감점 사유로 남겼다.
- 등급 기준
- `Pass`: 요구사항을 대체로 충족하고 치명적인 오동작이 보이지 않음
- `Warn`: 핵심 동작은 가능하지만 엣지 케이스, 재호출 안정성, 자원 정리, 구현 방식에 약점이 있음
- `Fail`: 요구사항과 다른 동작, 명확한 논리 오류, 잘못된 결과 가능성이 큼

## 전체 메모
- 전체 CMake 빌드는 성공했다.
- 빌드 경고 중 `main()` 프로토타입, 메뉴 변수 사용, 일부 프레임 초기화 문제는 제공 코드 성격이 강해서 본 평가에서 제외했다.
- `Binary_Search_Tree/Q5_F_BST.c`의 `removeNodeFromTree()`는 실제 과제 흐름에서 호출되지 않는 제공 스텁으로 보고 평가에서 제외했다.

## 유형별 정리

### 1. 순회 중 구조 크기 변경을 잘못 다룬 경우
- `Q1_C_SQ - removeOddValues`: `dequeue()`와 `enqueue()`로 queue 크기가 바뀌는데 루프 조건으로 `q->ll.size`를 직접 써서 원래 queue 전체를 한 번씩 처리하지 못한다.

### 2. 최대/최소 또는 깊이 계산 방향 오류
- `Q2_E_BT - maxHeight`: 좌우 높이 중 큰 값을 택해야 하는데 작은 값을 반환한다.
- `Q8_E_BT - hasGreatGrandchild`: 더 깊은 쪽을 기준으로 판단해야 하는데 더 얕은 쪽을 사용한다.

### 3. 재귀 분기 선택 또는 구조 비교 로직 오류
- `Q1_E_BT - identical`: 둘 다 `NULL`인 경우를 동일로 처리하지 못하고, 좌우 자식 비교 재귀 조건도 잘못되어 있다.
- `Q3_E_BT - countOneChildNodes`: 자식이 하나인 경우 존재하는 쪽이 아니라 `NULL` 쪽으로 재귀를 내려가 추가 집계를 놓친다.

### 4. 연결 구조 갱신 실수
- `Q2_A_LL - alternateMergeLinkedList`: 임시 리스트로 값만 복사한 뒤 `ll1` 헤드만 갈아끼워 원래 노드와 남은 요소 처리가 깨진다.
- `Q6_A_LL - moveMaxToFront`: 최대값이 이미 head인 경우 자기 자신을 가리키는 사이클을 만들 수 있다.

### 5. 제공 `main` 프레임의 상태 관리 한계
- `Q1_C_SQ`, `Q2_C_SQ`: `case 2` 전에 결과 queue/stack을 비우지 않아 같은 실행에서 재생성 시 누적된다. 다른 과제 파일 패턴과 비교하면 함수보다 `main` 쪽 책임에 더 가깝다고 본다.

### 6. 함수 내부 자원 정리 또는 반환 계약 문제
- `Q7_C_SQ - balanced`: 중간 실패 시 함수 내부 지역 stack 노드를 해제하지 않고 반환한다.
- `Q6_A_LL - moveMaxToFront`: 반환형이 `int`인데 값을 반환하지 않는다.

### 7. 빈 구조 또는 null 입력 방어 부족
- `Q1_F_BST - levelOrderTraversal`: 빈 트리에서도 `root`를 enqueue 하고 바로 역참조할 수 있다.
- `Q3_F_BST - preOrderIterative`: `root == NULL` 체크 없이 push 해서 빈 트리에서 역참조 위험이 있다.

### 8. 기능은 맞지만 구현이 비효율적인 경우
- `Q5_A_LL - frontBackSplitLinkedList`: 반복 `findNode()`로 `O(n^2)`에 가깝다.
- `Q3_A_LL - moveOddItemsToBack`, `Q4_A_LL - moveEvenItemsToBack`: 동작은 맞지만 반복 탐색으로 비효율적이다.

## Linked List

### Q1_A_LL - `insertSortedLL`
- 등급: `Pass`
- C 문법/구현: `curr`와 `idx`를 이용해 삽입 위치를 찾고, 중복이면 `-1`, 성공 시 인덱스를 반환하는 흐름이 깔끔하다.
- 알고리즘/자료구조: 정렬 상태를 유지하는 선형 탐색 + 기존 `insertNode()` 호출 구조라 의도에 맞다.
- 보완점: `ll == NULL` 방어가 없지만 현재 프레임 사용 방식에서는 큰 문제는 아니다.

### Q2_A_LL - `alternateMergeLinkedList`
- 등급: `Fail`
- C 문법/구현: 임시 리스트 `ll_tmp`를 새로 만들고 마지막에 `ll1->head`, `ll1->size`만 바꿔서 원래 `ll1`의 남은 노드가 끊긴다. 기존 노드 연결을 재사용하지 않아 메모리 누수 가능성도 크다.
- 알고리즘/자료구조: 두 리스트를 번갈아 병합해야 하는데, 현재 구현은 `min(size1, size2)`까지만 새 리스트로 복사하고 남는 `ll1` 요소를 버린다. 일반적인 alternate merge 요구와 어긋난다.
- 핵심 근거: 원본 노드를 재배치하지 않고 값만 복사하며, 남는 노드 처리 로직이 없다.

### Q3_A_LL - `moveOddItemsToBack`
- 등급: `Pass`
- C 문법/구현: 현재 인덱스를 유지하면서 홀수면 뒤에 추가 후 현재 위치를 삭제하는 방식이 안전하게 동작한다.
- 알고리즘/자료구조: 원래 길이 `end` 기준으로 한 번만 순회해서 원본 구간만 처리하므로, 뒤로 보낸 원소를 다시 검사하지 않는다.
- 보완점: `findNode()`를 반복 호출하므로 시간복잡도는 `O(n^2)`이지만 학습용 과제로는 허용 가능하다.

### Q4_A_LL - `moveEvenItemsToBack`
- 등급: `Pass`
- C 문법/구현: Q3와 같은 패턴으로 짝수만 뒤로 보내며 인덱스 관리도 일관된다.
- 알고리즘/자료구조: 기존 순서를 유지한 채 짝수만 뒤로 이동하는 로직으로 볼 수 있다.
- 보완점: 역시 `findNode()` 기반이라 `O(n^2)`이다.

### Q5_A_LL - `frontBackSplitLinkedList`
- 등급: `Warn`
- C 문법/구현: 앞 리스트 길이를 `(n / 2) + (n % 2)`로 계산한 것은 적절하다.
- 알고리즘/자료구조: 결과는 맞게 만들 가능성이 높지만, 매번 `findNode()`로 다시 찾으면서 복사하므로 비효율적이다.
- 보완점: 느린 포인터/빠른 포인터 또는 한 번의 순회로도 충분히 풀 수 있는 문제를 `O(n^2)`로 풀었다. 기능 면에서는 큰 오류가 보이지 않는다.

### Q6_A_LL - `moveMaxToFront`
- 등급: `Fail`
- C 문법/구현: 반환형이 `int`인데 값을 반환하지 않아 빌드 경고가 난다. 더 큰 문제는 최대값이 이미 head일 때 `max->next = head`가 되어 자기 자신을 가리키는 사이클을 만든다는 점이다.
- 알고리즘/자료구조: 최대 노드를 떼어 맨 앞으로 보내려는 접근 자체는 맞지만, `max_prev == NULL` 처리 분기가 빠져 있어 핵심 엣지 케이스를 망친다.
- 핵심 근거: `max`가 기존 head일 때 연결을 바꾸지 말아야 하는데 무조건 `max->next = head`를 수행한다.

### Q7_A_LL - `RecursiveReverse`
- 등급: `Pass`
- C 문법/구현: base case를 두고, 나머지 리스트를 재귀적으로 뒤집은 뒤 `next->next = curr`로 방향을 뒤집는 전형적인 재귀 역순 구현이다.
- 알고리즘/자료구조: 추가 자료구조 없이 포인터 재연결만으로 해결했고, `curr->next = NULL`도 넣어 사이클을 막았다.
- 보완점: `ListNode* curr`, `ListNode* next` 선언 위치가 중간에 있지만 C11 기준으로는 문제 없다.

## Stack and Queue

### Q1_C_SQ - `createQueueFromLinkedList`
- 등급: `Pass`
- C 문법/구현: 단순 순회 후 `enqueue()`로 복사하는 기본 동작은 맞다.
- 알고리즘/자료구조: queue가 이미 비어 있다는 전제가 맞으면 정상이다.
- 참고: 같은 실행에서 `case 2`를 여러 번 누르면 결과가 누적되지만, 다른 과제 파일들의 `main` 패턴과 비교하면 이 부분은 함수보다 제공 `main` 프레임 책임에 더 가깝다.

### Q1_C_SQ - `removeOddValues`
- 등급: `Fail`
- C 문법/구현: 짝수만 다시 enqueue 하려는 의도 자체는 맞게 고쳐졌지만, 루프 조건으로 `q->ll.size`를 직접 써서 순회 도중 바뀌는 크기에 영향을 받는다.
- 알고리즘/자료구조: 원래 queue 길이를 고정해 두고 그 횟수만큼 dequeue 해야 하는데, 현재 구현은 원소를 끝까지 한 번씩 처리하지 못한다.
- 실행 확인: 입력 `1,2`는 `2`만 남아 정상처럼 보이지만, `1,2,3`은 `2`가 아니라 `3 2`가 남는다.

### Q2_C_SQ - `createStackFromLinkedList`
- 등급: `Pass`
- C 문법/구현: 순회하면서 `push()`하므로 stack이 뒤집힌 형태로 만들어진다. stack 성질상 자연스러운 결과일 수 있다.
- 알고리즘/자료구조: linked list의 순서를 stack top 기준으로 옮기는 동작은 맞다.
- 참고: 같은 실행에서 `case 2`를 여러 번 누르면 결과가 누적되지만, 이는 제공 `main`의 상태 관리 문제로 본다.

### Q2_C_SQ - `removeEvenValues`
- 등급: `Pass`
- C 문법/구현: linked list 형태의 stack을 인덱스로 순회하면서 짝수 노드를 삭제하는 방식으로 수정됐다.
- 알고리즘/자료구조: 삭제 후 `i--`로 현재 위치를 다시 검사하는 처리도 적절하다.
- 실행 확인: 입력 `1,2`는 `1`, 입력 `1,2,3`은 `3 1`이 남아 의도와 맞는다.

### Q3_C_SQ - `isStackPairwiseConsecutive`
- 등급: `Pass`
- C 문법/구현: 두 개씩 `pop()`해서 각 pair의 절대값 차이가 1인지 확인하는 구조로 바뀌었다.
- 알고리즘/자료구조: 이번 평가에서는 “원소 수가 홀수면 pair가 완성되지 않으므로 false” 해석을 채택하며, 그 기준에서 현재 구현은 맞다.
- 실행 확인: `2 1`은 consecutive, `3 2 1`은 홀수 개 원소라 false로 판정된다.

### Q4_C_SQ - `reverse`
- 등급: `Pass`
- C 문법/구현: 지역 stack을 만들고 queue를 모두 pop/dequeue 후 다시 enqueue 하는 방식이 명확하다.
- 알고리즘/자료구조: stack을 이용한 queue reversal의 정석 구현이다.
- 보완점: 별도 약점은 크지 않다.

### Q5_C_SQ - `recursiveReverse`
- 등급: `Pass`
- C 문법/구현: base case 후 하나를 꺼내 재귀 호출 뒤 다시 넣는 구조로 재귀 stack을 잘 활용했다.
- 알고리즘/자료구조: 보조 자료구조 없이 queue를 역순으로 만드는 전형적인 풀이이다.
- 보완점: 별도 약점은 크지 않다.

### Q6_C_SQ - `removeUntil`
- 등급: `Pass`
- C 문법/구현: top이 원하는 값이 될 때까지 `pop()`하는 조건식이 간단하고 안전하다.
- 알고리즘/자료구조: stack의 top 기준 제거 요구에 맞는 구현이다.
- 보완점: 값을 찾지 못하면 stack이 비게 되는데, 보통 이런 의미의 문제에서는 허용되는 해석이다.

### Q7_C_SQ - `balanced`
- 등급: `Warn`
- C 문법/구현: 괄호 짝 검사 로직 자체는 맞다. 여는 괄호 push, 닫는 괄호에서 짝 비교도 적절하다.
- 알고리즘/자료구조: stack 활용 방식은 올바르다.
- 보완점: 바깥 `main`이 이 함수 내부의 지역 stack을 대신 정리해 줄 수는 없으므로, 중간에 불균형을 발견하고 바로 `return`하면 내부 stack 노드가 해제되지 않는다. 입력 문자가 괄호 외 문자를 포함하면 즉시 실패 처리하는 것도 문제 요구 해석에 따라 다를 수 있다.
- 제외: 간헐적 무한 루프는 `main` 쪽 입력 흐름 문제로 보이며 본 평가에서 제외한다.

## Binary Tree

### Q1_E_BT - `identical`
- 등급: `Fail`
- C 문법/구현: `tree1 == NULL || tree2 == NULL`이면 무조건 `NO_IDENTICAL`을 반환해서, 둘 다 `NULL`인 경우도 같다고 보지 못한다.
- 알고리즘/자료구조: 왼쪽/오른쪽 자식 재귀 조건이 `if (is_all_left && !is_once_left)`인데, 이 조건은 참이 될 수 없다. 결과적으로 자식 비교 재귀가 거의 수행되지 않는다.
- 핵심 근거: 구조 비교의 base case와 재귀 조건 둘 다 잘못되어 있어 사실상 루트 값만 비교하는 코드에 가깝다.

### Q2_E_BT - `dfs`, `maxHeight`
- 등급: `Fail`
- C 문법/구현: 보조 함수 `dfs()`를 추가해 높이를 계산하려는 시도는 가능하다.
- 알고리즘/자료구조: 높이는 왼쪽/오른쪽 서브트리 중 큰 값을 택해야 하는데, 현재 코드는 `return ll < rl ? ll : rl;`로 더 작은 쪽을 반환한다.
- 핵심 근거: `maxHeight()`가 실제로는 최소 깊이에 가까운 값을 내므로 함수 목적과 반대다.

### Q3_E_BT - `countOneChildNodes`
- 등급: `Fail`
- C 문법/구현: `node == NULL` 처리 자체는 있다.
- 알고리즘/자료구조: 한쪽 자식만 있는 경우 현재 노드만 `+1` 하고, 존재하는 자식 쪽이 아니라 `NULL` 쪽으로 재귀를 내려가 버린다. 예를 들어 오른쪽 자식만 있으면 `countOneChildNodes(node->left) + 1`을 호출한다.
- 핵심 근거: 존재하는 서브트리 내부의 추가 one-child 노드를 전혀 세지 못한다.

### Q4_E_BT - `sumOfOddNodes`
- 등급: `Pass`
- C 문법/구현: `node == NULL`이면 0, 아니면 현재 노드가 홀수일 때만 값을 더하는 구조가 명확하다.
- 알고리즘/자료구조: 전체 트리를 재귀적으로 순회하며 홀수 노드 합계를 계산하므로 요구에 맞다.

### Q5_E_BT - `mirrorTree`
- 등급: `Pass`
- C 문법/구현: 좌우 서브트리를 먼저 미러링한 뒤 현재 노드의 left/right를 swap한다.
- 알고리즘/자료구조: 추가 트리 생성 없이 제자리에서 뒤집는 요구에 잘 맞는다.

### Q6_E_BT - `printSmallerValues`
- 등급: `Pass`
- C 문법/구현: 기준값 `m`보다 작은 값만 출력하고, `NULL`이면 종료한다.
- 알고리즘/자료구조: 전체 트리를 전위 순회하면서 조건을 만족하는 노드를 출력하는 방식이다.
- 보완점: 문제지에서 출력 순서를 엄격히 요구했다면 별도 대조가 필요하지만, 현재 코드만 놓고 보면 자연스럽다.

### Q7_E_BT - `smallestValue`
- 등급: `Pass`
- C 문법/구현: `NULL`일 때 `INT_MAX`를 반환하고, 현재 값과 좌우 최솟값을 비교해 최소를 구한다.
- 알고리즘/자료구조: 재귀 최솟값 탐색으로 적절하다.
- 보완점: 빈 트리에서 `INT_MAX`가 반환된다는 점은 프레임 호출 방식에 의존한다.

### Q8_E_BT - `hasGreatGrandchild`
- 등급: `Fail`
- C 문법/구현: 반환값을 깊이처럼 쓰려는 의도는 보인다.
- 알고리즘/자료구조: great-grandchild 존재 여부를 판단하려면 더 깊은 쪽 기준이 필요하지만, 현재 코드는 `ll < rl ? ll : rl`로 더 작은 쪽을 택한다. 즉 한쪽 서브트리만 깊어도 만족해야 할 조건을 놓친다.
- 핵심 근거: `max depth`가 아니라 `min depth` 기반으로 판정해 깊은 한쪽 가지를 제대로 반영하지 못한다.

## Binary Search Tree

### Q1_F_BST - `levelOrderTraversal`
- 등급: `Warn`
- C 문법/구현: root를 queue에 넣고 좌우 자식을 순서대로 넣는 BFS 구조는 맞다.
- 알고리즘/자료구조: level-order traversal 구현 자체는 적절하다.
- 보완점: `root == NULL`일 때도 바로 enqueue 후 `node->item`을 역참조하므로 빈 트리 출력에서 crash 가능성이 있다.

### Q2_F_BST - `inOrderTraversal`
- 등급: `Pass`
- C 문법/구현: 왼쪽 끝까지 push 후 pop, 방문, 오른쪽 이동의 iterative in-order 패턴을 정확히 사용했다.
- 알고리즘/자료구조: stack 기반 중위 순회로 적절하다.
- 보완점: 별도 약점은 크지 않다.

### Q3_F_BST - `preOrderIterative`
- 등급: `Warn`
- C 문법/구현: root를 push하고 pop하면서 right, left 순으로 넣는 전위 순회 패턴은 맞다.
- 알고리즘/자료구조: 비어 있지 않은 BST에서는 정상 동작한다.
- 보완점: `root == NULL` 체크 없이 바로 `push(&s, root)` 하므로 빈 트리에서 `node->item` 역참조 위험이 있다.

### Q4_F_BST - `postOrderIterativeS1`
- 등급: `Pass`
- C 문법/구현: `last_visited`를 이용한 one-stack post-order 구현이 올바른 형태다.
- 알고리즘/자료구조: 왼쪽 끝까지 내려간 뒤 오른쪽 방문 여부를 확인하는 전형적인 iterative post-order 풀이이다.

### Q5_F_BST - `postOrderIterativeS2`
- 등급: `Pass`
- C 문법/구현: `root == NULL` 방어 후, 두 개의 stack을 이용해 역전된 post-order를 출력하는 구조가 맞다.
- 알고리즘/자료구조: two-stack post-order의 표준 풀이이다.
- 제외: 같은 파일의 `removeNodeFromTree()`는 실제 과제 수행 경로에 쓰이지 않는 제공 스텁이라 본 평가에서 제외했다.

## 요약
- `Pass`: Q1_A_LL, Q3_A_LL, Q4_A_LL, Q7_A_LL, Q2_C_SQ, Q3_C_SQ, Q4_C_SQ, Q5_C_SQ, Q6_C_SQ, Q4_E_BT, Q5_E_BT, Q6_E_BT, Q7_E_BT, Q2_F_BST, Q4_F_BST, Q5_F_BST
- `Warn`: ~~Q5_A_LL~~, ~~Q1_C_SQ~~, ~~Q7_C_SQ~~, ~~Q1_F_BST~~, ~~Q3_F_BST~~
- `Fail`: ~~Q2_A_LL~~, ~~Q6_A_LL~~, ~~Q1_E_BT~~, ~~Q2_E_BT~~, ~~Q3_E_BT~~, ~~Q8_E_BT~~
- 1차 결론: Stack and Queue 1~3은 다시 보면 Q1만 핵심 로직 수정이 더 필요하고, Q2와 Q3는 현재 해석 기준에서 통과권이다. 여전히 큰 우선순위는 `Binary_Tree` 계열의 재귀 로직과 Linked List 일부 포인터 갱신 문제다.

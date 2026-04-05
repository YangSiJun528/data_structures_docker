# CZ1007 Data Structures 후속 해결 여부 점검

## 개요
- 기준 문서: `reports/001_initial-evaluation.md`
- 점검 기준: `001`에서 `Warn` 또는 `Fail`로 분류된 항목
- 확인 방법
- 이후 커밋 이력 확인
- 현재 HEAD 기준 코드 정적 검토
- 반례가 명확한 항목은 실행 파일 재빌드 후 직접 실행 확인
- 점검 시점 HEAD: `be5bac3` (`Binary_Search_Tree 문제 해결`)

## 관련 커밋
- `f34a720` `오답 체크리스트 추가 및 Stack&Queue 문제 해결`
- `3941743` `Binary Tree 문제 해결`
- `3305c4d` `Linked List 문제 해결`
- `be5bac3` `Binary_Search_Tree 문제 해결`

## 재평가 결과

| 항목 | 001 등급 | 현재 판단 | 근거 |
|---|---|---|---|
| `Q5_A_LL - frontBackSplitLinkedList` | Warn | 해결 처리 | 성능상 `findNode()` 반복 호출로 `O(n^2)`에 가까운 점은 남아 있지만, 과제에서 제공한 함수 사용 범위 안의 구현이며 사용자가 해당 비효율을 인지한 상태에서 허용 가능한 풀이로 보기로 했다. 즉 기능 실패가 아니라 구현 선택 문제로 정리한다. |
| `Q1_C_SQ - removeOddValues` | Fail | 해결 | `q->ll.size`를 루프 중 직접 참조하던 문제를 고쳐 초기 `count`만큼만 순회한다. 실행 확인에서도 입력 `1 2 3`에서 결과 queue가 `2`만 남았다. |
| `Q7_C_SQ - balanced` | Warn | 해결 처리 | 중간 실패 시 지역 stack을 함수 내부에서 비우지 않는 점은 남아 있지만, 사용자는 이를 과제 풀이 함수의 책임이 아니라 제공 `main` 프레임 또는 호출부 책임으로 본다. 이번 후속 판정에서는 함수 내부 로직 오류가 아닌 프레임 책임 문제로 제외한다. |
| `Q1_F_BST - levelOrderTraversal` | Warn | 해결 | 함수 시작부에 `if (root == NULL) return;` 방어가 추가되었다. 빈 트리에서 메뉴 `2`를 바로 눌러도 crash 없이 종료한다. |
| `Q3_F_BST - preOrderIterative` | Warn | 해결 | 함수 시작부에 `if (root == NULL) return;` 방어가 추가되었다. 빈 트리에서 메뉴 `2`를 바로 눌러도 crash 없이 종료한다. |
| `Q2_A_LL - alternateMergeLinkedList` | Fail | 해결 | 임시 리스트로 `head`만 갈아끼우는 방식이 사라지고, `ll2`의 앞 원소를 `ll1`에 교차 삽입하는 구조로 바뀌었다. 실행 확인에서 `ll1 = 1 2 3 4 5`, `ll2 = 9 8` 입력 시 `ll1 = 1 9 2 8 3 4 5`, `ll2 = Empty`가 출력됐다. |
| `Q6_A_LL - moveMaxToFront` | Fail | 해결 | `max != head`일 때만 `max->next = head`를 수행하도록 바뀌어 head가 이미 최대값일 때 self-loop가 생기지 않는다. 반환값도 추가돼 반환형 경고 원인도 제거됐다. |
| `Q1_E_BT - identical` | Fail | 해결 | `NULL/NULL`을 동일로 처리하고, 좌우 자식 비교를 직접 재귀 호출하도록 수정됐다. 빈 트리 두 개 비교에서 identical로 동작한다. |
| `Q2_E_BT - maxHeight` | Fail | 해결 | `dfs()`가 더 깊은 쪽을 반환하도록 바뀌었다. 편향 트리 반례에서 높이 `2`가 출력됐다. |
| `Q3_E_BT - countOneChildNodes` | Fail | 해결 | 자식이 하나인 경우 존재하는 쪽으로 재귀를 내려가도록 수정됐다. 한쪽으로만 이어진 3노드 트리에서 결과 `2`가 출력됐다. |
| `Q8_E_BT - hasGreatGrandchild` | Fail | 해결 | 깊은 쪽을 고르는 로직에 더해 출력 임계값도 `level >= 4`로 수정됐다. 실행 확인 결과 `1 -> 2 -> 3` 체인에서는 아무 것도 출력되지 않았고, `1 -> 2 -> 3 -> 4` 체인에서는 `1`만 출력됐다. |

## 실행 확인 메모
- 빌드 성공
- `Stack_and_Queue_Q1_C_SQ`
- `Linked_List_Q2_A_LL`
- `Linked_List_Q6_A_LL`
- `Binary_Tree_Q1_E_BT`
- `Binary_Tree_Q2_E_BT`
- `Binary_Tree_Q3_E_BT`
- `Binary_Tree_Q8_E_BT`
- `Binary_Search_Tree_Q1_F_BST`
- `Binary_Search_Tree_Q3_F_BST`
- 확인한 대표 실행 결과
- `Q1_C_SQ`: `1 2 3` -> remove odd -> `2`
- `Q2_A_LL`: `1 2 3 4 5` + `9 8` -> `1 9 2 8 3 4 5`
- `Q6_A_LL`: `9 3 1` -> move max -> `9 3 1` 유지, 무한 루프 없음
- `Q2_E_BT`: 편향 트리 높이 `2`
- `Q3_E_BT`: one-child 노드 수 `2`
- `Q1_F_BST`, `Q3_F_BST`: 빈 트리에서 순회 메뉴 선택 시 crash 없음
- `Q8_E_BT`: 3노드 체인에서는 출력 없음, 4노드 체인에서는 `1`만 출력

## 결론
- `001`에서 비통과였던 11개 항목은 모두 해결 또는 해결 처리로 정리했다.
- 현재 기준으로 실제 미해결 항목은 없다.
- `Q5_A_LL`, `Q7_C_SQ`는 각각 “과제 제공 함수 사용에 따른 비효율”과 “제공 프레임 책임”으로 해석해 이번 후속 판정에서 해제했다.
- 따라서 `reports/001_initial-evaluation.md` 마지막 요약에서 모든 `Warn`/`Fail` 항목을 취소선 처리한 현재 상태는 이번 후속 판단과 일치한다.

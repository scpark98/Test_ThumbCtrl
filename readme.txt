
[생성방식]
- resource editor에 추가하는 정적 생성방식이 아닌 CSCThumbCtrl의 create()을 통한 동적 생성방식 사용
- m_thumb.set_path(...)를 호출하여 해당 폴더내의 모든 이미지 파일들을 thumb로 표시한다.
- MAX_THUMB_WIDTH, MAX_THUMB_HEIGHT 크기로 resize하여 관리해야 속도가 느려지지 않는다.

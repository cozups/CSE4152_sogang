import React from "react";
import styled from "styled-components";

import ChatLogItem from "./ChatLogItem";


function ChatLogTemplate({chats}) {

  // chats 배열을 받아 저장해 둔 채팅 로그를 보여줌
  // ChatLogItem 컴포넌트 사용
  return (
    
    <ChatContainer>
      <h1>Chat Log</h1>
      {/* 8주차 실습 구현 */}
      {
        chats.map((chat) => {
          return <ChatLogItem chat={chat}/>
        })
      }
    </ChatContainer>
  );

}

const ChatContainer = styled.div`  
  width: 500px;
  margin: 10px;
  padding: 20px;
  // 해당 영역 모서리를 둥글게
  border-radius: 20px 20px 20px 20px;
  // 해당 영역 모서리에 그림자
  box-shadow: 0px 0px 10px #000;
  // 해당 영역의 배경색 변경
  background-color: #ffe082;
  // 8주차 실습 구현
`;

export default ChatLogTemplate;
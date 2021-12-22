// 채팅 키워드 검색창 & 검색 버튼에 대한 컴포넌트 작성
import React, {useState} from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";

function ChatSearch({onSearchKeySubmit}) {
    const [keyword, setKeyword] = useState("");

    const handleChange = (e) => {
        setKeyword(e.target.value);
    };

    const handleKeyPress = (e) => {
        e.preventDefault();
        if (!keyword) return;
        onSearchKeySubmit(keyword);
        setKeyword("");
    };
    return (
        <Form onSubmit={handleKeyPress}>
            <Box>
            <TextField
                name="keyword"
                id="outlined-multiline-static"
                variant="outlined"
                label="Keyword"
                type="text"
                value={keyword}
                onChange={handleChange}
            />
            <Button>Search</Button>
            </Box>
        </Form>
    );
}

const Box = styled.div`
    margin: 30px;
`;
const Button = styled.button`
    margin: 10px;
    padding: 10px;
    background-color: white;
    border-color: #c8a951;
    border-radius: 5px;
`;
const Form = styled.form`
    display:"inline-block"
`;
export default ChatSearch;
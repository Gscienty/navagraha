import React from 'react';
import { connect } from 'react-redux';
import AceEditor from 'react-ace';
import { Modal } from 'antd';

import {
    resetCode,
    submitCode,
    CODE_TEMPLATE_SELECTED_UNSET
} from '../actions/code';

import 'brace/mode/java';
import 'brace/mode/python';
import 'brace/theme/github';
import 'brace/keybinding/vim';

class CodeEditor extends React.Component {

    constructor(props) {
        super(props);

        this.props.dispatch(resetCode());
    }

    state = {
        content: ''
    };

    shouldComponentUpdate(nextProps, nextState) {
        if (nextProps.selectedType !== this.props.selectedType) {
            nextState.content = nextProps.selectedContent;
        }
        if (nextProps.toggle !== this.props.toggle) {
            if (this.props.selectedState === CODE_TEMPLATE_SELECTED_UNSET) {
                Modal.error({ title: '错误', content: '您尚未设置函数类型。', onOk: () => Modal.destroyAll() });
            }
            else {
                this.props.dispatch(submitCode(this.props.selectedType, this.state.content));
            }
        }
        return true;
    }

    render() {
        return (
            <div>
                <AceEditor
                    onChange={v => this.setState({ content: v })}
                    value={this.state.content}
                    readOnly={this.props.selectedState === CODE_TEMPLATE_SELECTED_UNSET}
                    width='100%'
                    height='303px'
                    mode="java"
                    theme="github"
                    name="code-editor"
                    editorProps={{$blockScrolling: true}}
                    keyboardHandler="vim" />
            </div>
        );
    }
};

export default connect(({ code }) => ({
    selectedState: code.selectedTemplateState,
    selectedType: code.selectedTemplateType,
    selectedContent: code.selectedTemplateContent,
    toggle: code.submitToggle
}))(CodeEditor);


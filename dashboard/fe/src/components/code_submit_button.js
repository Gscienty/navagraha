import React from 'react';
import { connect } from 'react-redux';
import { Button } from 'antd';

import {
    resetCode,
    codeResetMetadata,
    submitToggle,
    CODE_METADATA_SET,
    CODE_SUBMIT_SET
} from '../actions/code';

class CodeSubmitButton extends React.Component {

    shouldComponentUpdate(nextProps, nextState) {
        if (nextProps.metadataState === CODE_METADATA_SET && nextProps.codeInfoState === CODE_SUBMIT_SET) {

            this.props.dispatch(codeResetMetadata());
            this.props.dispatch(resetCode());
        }

        return false;
    }

    render() {
        return (
            <Button
                type="primary"
                onClick={() => this.props.dispatch(submitToggle())}>
                提交
            </Button>
        )
    }
};

export default connect(({ code }) => ({
    metadataState: code.codeMetadataState,
    codeInfoState: code.codeInfoState,

    metadata: code.codeMetadata,
    codeInfo: code.codeInfo
}))(CodeSubmitButton);

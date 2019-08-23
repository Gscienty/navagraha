import React from 'react';
import { connect } from 'react-redux';
import { Button, Modal, Progress } from 'antd';

import {
    codeBuild,
    resetCode,
    codeResetMetadata,
    submitToggle,
    CODE_METADATA_SET,
    CODE_SUBMIT_SET,
    CODE_BUILD_RUNNING
} from '../actions/code';

class CodeSubmitButton extends React.Component {

    state = { process: 0 }

    shouldComponentUpdate(nextProps, nextState) {
        if (this.props.buildState !== CODE_BUILD_RUNNING
        && nextProps.buildState !== CODE_BUILD_RUNNING
        && nextProps.metadataState === CODE_METADATA_SET
        && nextProps.codeInfoState === CODE_SUBMIT_SET) {

            this.props.dispatch(codeBuild({
                name: nextProps.metadata.name,
                version: nextProps.metadata.version,
                content: nextProps.codeInfo.content,
                type: nextProps.codeType
            }));

            this.props.dispatch(codeResetMetadata());
            this.props.dispatch(resetCode());
        }

        return nextProps.buildState === CODE_BUILD_RUNNING
        || this.props.buildState === CODE_BUILD_RUNNING;
    }

    render() {
        return (
            <div>
            <Button
                type="primary"
                loading={this.props.buildState === CODE_BUILD_RUNNING}
                onClick={() => this.props.dispatch(submitToggle())}>
                提交
            </Button>

            <Modal
                closable={false}
                footer={null}
                maskClosable={false}
                visible={this.props.buildState === CODE_BUILD_RUNNING}
                title="函数构建中..."
                bodyStyle={{ textAlign: 'center' }}>
                <label style={{ textAlign: 'left' }}>构建进度：</label>
                <Progress
                    type="line"
                    status="active"
                    strokeWidth={10}
                    percent={ Math.round(this.props.buildingProcess * 100) } />
                <br />
            </Modal>
            </div>
        )
    }
};

export default connect(({ code }) => ({
    metadataState: code.codeMetadataState,
    codeInfoState: code.codeInfoState,

    metadata: code.codeMetadata,
    codeInfo: code.codeInfo,

    codeType: code.selectedTemplateType,

    buildState: code.codeBuildState,

    buildingInfo : code.codeBuildingLastInfo,
    buildingProcess: code.codeBuildingProcess
}))(CodeSubmitButton);

import React from 'react';
import { connect } from 'react-redux';
import { Form, Input } from 'antd';

import {
    codeResetMetadata,
    codeChangeMetadata
} from '../actions/code';

class CodeMetadataForm extends React.Component {

    constructor(props) {
        super(props);

        this.props.dispatch(codeResetMetadata());
    }

    shouldComponentUpdate(nextProps, nextState) {
        if (nextProps.toggle !== this.props.toggle) {
            this.props.form.validateFields((err, values) => {
                this.props.dispatch(codeChangeMetadata(values));
            });
        }
        return true;
    }

    render() {
        const { getFieldDecorator } = this.props.form

        const layout = {
            labelCol: { xs: { span: 24 }, sm: { span: 8 } },
            wrapperCol: { xs: { span: 24 }, sm: { span: 16 } }
        };


        return (
            <Form layout="inline" hideRequiredMark={true}>
                <Form.Item { ...layout } label="函数名">
                    {getFieldDecorator('name', {
                    })(
                        <Input placeholder="请输入函数名称" />
                    )}
                </Form.Item>
                <Form.Item { ...layout } label="版本号">
                    {getFieldDecorator('version', {
                    })(
                        <Input placeholder="请输入函数版本号" />
                    )}
                </Form.Item>
            </Form>
        );
    }
};

export default connect(({ code }) => ({
    toggle: code.submitToggle
}))(Form.create({ validateMessages: null })(CodeMetadataForm));


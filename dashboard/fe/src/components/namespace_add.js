import React from 'react'
import { connect } from 'react-redux';
import { Button, Drawer, Form, Row, Col, Input } from 'antd';
import {
    addNamespace
} from '../actions/namespace';

class NamespaceAdd extends React.PureComponent {

    state = { drawerVisible: false };

    onClose = () => { this.setState({ drawerVisible: false }); }

    handleSubmit = e => {
        e.preventDefault();
        this.props.form.validateFields((err, values) => {
            if (!err) {
                this.props.dispatch(addNamespace(values.namespace));
                this.onClose();

                this.props.form.setFieldsValue({
                    namespace: ''
                });
            }
        });
    }

    render() {
        const { getFieldDecorator } = this.props.form;
        return (
            <span>
                <Button
                    type='primary'
                    onClick={() => { this.setState({ drawerVisible: true }); }}>新建命名空间</Button>
                <Drawer
                    title='新建命名空间'
                    visible={this.state.drawerVisible}
                    width={720}
                    onClose={this.onClose}>
                    <Form
                        layout='vertical'
                        onSubmit={this.handleSubmit}
                        hideRequiredMark>
                        <Row gutter={16}>
                            <Col span={16}>
                                <Form.Item label='名称'>
                                    {getFieldDecorator('namespace', {
                                        rules: [{ required: true, message: '请输入命名空间名称' }]
                                    })(<Input placeholder='请输入命名空间名称' />)}
                                </Form.Item>
                            </Col>
                        </Row>
                        <div style={{
                            position: 'absolute',
                            left: 0,
                            bottom: 0,
                            width: '100%',
                            borderTop: '1px solid #e9e9e9',
                            textAlign: 'right',
                            padding: '10px 16px'
                        }}>
                            <Button style={{ marginRight: 8 }} onClick={this.onClose}>取消</Button>
                            <Button type='primary' htmlType='submit'>新建</Button>
                        </div>
                    </Form>
                </Drawer>
            </span>
        );
    }
};

export default connect()(Form.create()(NamespaceAdd));

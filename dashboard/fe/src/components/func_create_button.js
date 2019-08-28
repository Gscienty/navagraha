import React from 'react';
import { connect } from 'react-redux';
import { Form, Button, Drawer, Row, Col, Select, InputNumber, Switch, Input } from 'antd';
import NamespaceSelectorButton from '../components/namespace_selector';

import {
    fetchFuncRepoList,
    FUNC_REPO_LIST_UNSET,
} from '../actions/repo';

import {
    upFunc
} from '../actions/func';

//import {
    //NAMESPACE_LIST_UNSET
//} from '../actions/namespace';

class FuncCreateButton extends React.PureComponent {

    FRESH_INTERVAL = 1000;
    WAITING_HANDLER = 0;

    state = {
        drawerVisible: false,
        selectedRepoName: ''
    };

    constructor(props) {
        super(props);

        if (this.props.repo.state === FUNC_REPO_LIST_UNSET) {
            this.props.dispatch(fetchFuncRepoList());
        }

        this.WAITING_HANDLER = setInterval(() => {
            this.props.dispatch(fetchFuncRepoList());
        }, this.FRESH_INTERVAL);
    }

    componentWillUnmount() {
        clearInterval(this.WAITING_HANDLER);
    }

    drawerOnClose = () => this.setState({ drawerVisible: false });

    handleSubmit = e => {
        e.preventDefault();
        this.props.form.validateFields((err, values) => {
            if (!err) {
                values.stateful = !!values.stateful;
                this.drawerOnClose();
                this.props.dispatch(upFunc({
                    name: values.name,
                    namespace: this.props.namespace.selectedNamespace,
                    policy: values.policy,
                    image: values.repoName + ':' + values.repoVersion,
                    stateful: values.stateful,
                    update: false,
                    replicas: values.replicas
                }));
            }
        });
    };

    render() {
        const { getFieldDecorator } = this.props.form;

        const formLayout = {
            labelCol: { sm: { span: 8 } },
            wrapperCol: { sm: { span: 16 } }
        };

        return (<span>
                    <Button key="new" type="primary" onClick={() => this.setState({drawerVisible: true})}>创建函数服务</Button>
                    <Drawer
                        visible={this.state.drawerVisible}
                        title={<span>创建函数服务 <span style={{marginLeft: 24}}><NamespaceSelectorButton /></span></span>}
                        onClose={this.drawerOnClose}
                        width={720}>
                        <Form
                            {...formLayout}
                            onSubmit={this.handleSubmit}>
                            <Row gutter={24}>
                                <Col span={12}>
                                    <Form.Item label="服务名称">
                                        {getFieldDecorator("name", { })(
                                            <Input />
                                        )}
                                    </Form.Item>
                                </Col>
                            </Row>
                            <Row gutter={24}>
                                <Col span={12}>
                                    <Form.Item label="镜像名称">
                                        {getFieldDecorator('repoName', { })(
                                            <Select onSelect={e => this.setState({ selectedRepoName: e })}>
                                                {this.props.repo.repo.map(repo => (
                                                    <Select.Option key={repo.name} value={repo.name}>{repo.name}</Select.Option>
                                                ))}
                                            </Select>
                                        )}
                                    </Form.Item>
                                </Col>
                                <Col span={12}>
                                    <Form.Item label="镜像版本">
                                        {getFieldDecorator('repoVersion', { })(
                                            <Select>
                                                {(() => {
                                                    let ret = this.props.repo.repo
                                                        .find(r => r.name === this.state.selectedRepoName);
                                                    if (ret) {
                                                        return ret.versions.map(v => (
                                                            <Select.Option key={v} value={v}>{v}</Select.Option>
                                                        ));
                                                    }
                                                    else {
                                                        return [];
                                                    }
                                                })()}
                                            </Select>
                                        )}
                                    </Form.Item>
                                </Col>
                            </Row>

                            <Row gutter={24}>
                                <Col span={12}>
                                    <Form.Item label="初始副本数">
                                        {getFieldDecorator("replicas", { })(
                                            <InputNumber />
                                        )}
                                    </Form.Item>
                                </Col>
                            </Row>
                            <Row gutter={24}>
                                <Col span={12}>
                                    <Form.Item label="镜像拉取策略">
                                        {getFieldDecorator("policy", { })(
                                            <Select>
                                                <Select.Option key="never" value="Never">从不拉取镜像</Select.Option>
                                                <Select.Option key="always" value="Always">总是拉取镜像</Select.Option>
                                                <Select.Option key="IfNotPresent" value="IfNotPresent">若本地不存在则拉取镜像</Select.Option>
                                            </Select>
                                        )}
                                    </Form.Item>
                                </Col>
                            </Row>
                            <Row gutter={24}>
                                <Col span={12}>
                                    <Form.Item label="服务状态">
                                        {getFieldDecorator("stateful", { })(
                                            <Switch checkedChildren="有" unCheckedChildren="无" />
                                        )}
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
                                <Button style={{ marginRight: 8 }} onClick={this.drawerOnClose}>取消</Button>
                                <Button type='primary' htmlType='submit'>创建</Button>
                            </div>
                        </Form>
                    </Drawer>
                </span>)
    }
};

export default connect(({ repo, namespace }) => ({
    repo: repo.funcRepo,
    namespace
}))(Form.create()(FuncCreateButton));

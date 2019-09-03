import React from 'react';
import {
    Table,
    Tag,
    Button,
    Popover,
    Row,
    Col,
    Drawer,
    Descriptions,
    Select
} from 'antd';
import { connect } from 'react-redux';
import {
    selectDisplayNamespace,
    fetchNamespaces,
    deleteNamespace,
    NAMESPACE_LIST_SET,
    NAMESPACE_LIST_UNSET,
    NAMESPACE_SELECTED_SET,

    addNamespaceGateway,
    deleteNamespaceGateway
} from '../actions/namespace';

import {
    GATEWAY_REPO_LIST_UNSET,
    fetchGatewayRepoList
} from '../actions/repo';

class NamespaceList extends React.PureComponent {

    state = {
        drawerVisible: false,
        selectedNamespace: null,
        namespaceAPIGatewayRepo: '',
        policy: 'Never'
    };

    FRESH_INTERVAL = 5000;
    WAITING_HANDLER = 0;

    constructor(props) {
        super(props);

        if (this.props.namespace.state === NAMESPACE_LIST_UNSET
            || this.props.namespace.namespace.find(n => n.status !== 'Active')) {
            this.props.dispatch(fetchNamespaces());
        }

        if (this.props.repo.state === GATEWAY_REPO_LIST_UNSET) {
            this.props.dispatch(fetchGatewayRepoList());
        }

        this.WAITING_HANDLER = setInterval(() => {
            this.props.dispatch(fetchNamespaces());
        }, this.FRESH_INTERVAL);
    }

    componentWillUnmount() {
        clearInterval(this.WAITING_HANDLER);
    }

    drawerOnClose = () => this.setState({ drawerVisible: false });

    handleAddAPIGateway = () => {
        if (this.state.selectedNamespace === null
            || this.state.namespaceAPIGatewayRepo === ''
            || this.state.policy === '') {
            return;
        }

        this.props.dispatch(addNamespaceGateway(this.state.selectedNamespace.namespaceName,
                                               this.state.namespaceAPIGatewayRepo,
                                               this.state.policy));
        this.setState({ drawerVisible: false });
    };

    handleDeleteAPIGateway = () => {
        if (this.state.selectedNamespace === null) {
            return;
        }
        this.props.dispatch(deleteNamespaceGateway(this.state.selectedNamespace.namespaceName));
        this.setState({ drawerVisible: false });
    };

    render() {

        const COLUMNS = [
            {
                title: '名称',
                dataIndex: 'namespaceName',
                key: 'namespaceName'
            },
            {
                title: '状态',
                dataIndex: 'namespaceStatus',
                key: 'namespaceStatus'
            },
            {
                title: 'API网关',
                key: 'namespaceAPIGateway',
                render: n => n.namespaceGateway === null
                ? (<Tag key='n'>无</Tag>)
                : (<Tag key='y'>有</Tag>)
            },
            {
                title: '监控',
                key: 'namespaceMonitor',
                render: n => n.namespaceMonitor === null
                ? (<Tag key='n'>无</Tag>)
                : (<Tag key='y'>有</Tag>)
            },
            {
                title: '操作',
                key: 'operation',
                render: n => (
                    <div>
                        {
                            this.props.namespace.selectedState === NAMESPACE_SELECTED_SET
                            && this.props.namespace.selectedNamespace === n.namespaceName
                              ? <Tag key={n.namespaceName} closable={false} color='#108ee9'>已选择</Tag>
                              : <Button
                                  type='primary'
                                  size='small'
                                  onClick={() => this.props.dispatch(selectDisplayNamespace(n.namespaceName))}>
                                  选择
                              </Button>
                        }

                        &nbsp;

                        <Button
                        size='small'
                        onClick={() => this.setState({
                            drawerVisible: true,
                            selectedNamespace: n,
                            namespaceAPIGatewayRepo: '',
                            policy: ''
                        })}>
                        设置
                        </Button>

                        &nbsp;

                        {
                            n.namespaceStatus === 'Terminating'
                                ? <Tag key={n.namespaceName} closable={false} color='#f50'>移除中...</Tag>
                                : (
                                    this.props.namespace.selectedState === NAMESPACE_SELECTED_SET
                                    && this.props.namespace.selectedNamespace === n.namespaceName
                                        ? <span></span>
                                        : <Button size='small' onClick={() => this.props.dispatch(deleteNamespace(n.namespaceName))}>删除</Button>
                                )
                        }
                    </div>
                )

            }
        ];
        let dataSource = [];
        if (this.props.namespace.state === NAMESPACE_LIST_SET) {
            this.props.namespace.namespace
            .map(n => dataSource.push({
                key: n.name,
                namespaceName: n.name,
                namespaceStatus: n.status,
                namespaceGateway: n.gatewayInfo,
                namespaceMonitor: null
            }));
        };

        return (
            <div>
                <Table columns={COLUMNS} dataSource={dataSource} />

                <Drawer
                    title={
                        this.state.selectedNamespace === null
                        ? ''
                        : `设置命名空间 ${this.state.selectedNamespace.namespaceName}`
                    }
                    visible={this.state.drawerVisible}
                    width={720}
                    onClose={this.drawerOnClose}>

                    {(() => {
                        if (this.state.selectedNamespace === null) {
                            return (<span></span>);
                        }

                        return (
                            <div>
                                <Descriptions
                                    title="API 网关">
                                    <Descriptions.Item label="是否存在">
                                        {
                                            this.state.selectedNamespace.namespaceGateway === null
                                                ? "无"
                                                : "有"
                                        }
                                    </Descriptions.Item>
                                    <Descriptions.Item label="所属命名空间">
                                        {
                                            this.state.selectedNamespace.namespaceGateway === null
                                                ? "无网关"
                                                : this.state.selectedNamespace.namespaceGateway.namespace
                                        }
                                    </Descriptions.Item>
                                    <Descriptions.Item label="私有云IP地址">
                                        {
                                            this.state.selectedNamespace.namespaceGateway === null
                                                ? "无网关"
                                                : this.state.selectedNamespace.namespaceGateway.clusterIP
                                        }
                                    </Descriptions.Item>
                                    <Descriptions.Item label="API版本">
                                        {
                                            this.state.selectedNamespace.namespaceGateway === null
                                                ? "无网关"
                                                : this.state.selectedNamespace.namespaceGateway.imageTag
                                        }
                                    </Descriptions.Item>
                                </Descriptions>
                                <div style={{float: 'right', marginRight: 20}}>
                                {
                                    this.state.selectedNamespace.namespaceGateway === null
                                        ? (
                                            <div>
                                                <Select dropdownMatchSelectWidth={false} onSelect={n => this.setState({ policy: n })}>
                                                    <Select.Option key="never" value="Never">从不拉取镜像</Select.Option>
                                                    <Select.Option key="always" value="Always">总是拉取镜像</Select.Option>
                                                    <Select.Option key="IfNotPresent" value="IfNotPresent">若本地不存在则拉取镜像</Select.Option>
                                                </Select>
                                                <Select dropdownMatchSelectWidth={false} onSelect={n => this.setState({ namespaceAPIGatewayRepo: n })}>
                                                    {
                                                        this.props.repo.repo.map(n => (
                                                            <Select.Option key={n.name} value={n.name + ":" + n.version}>
                                                                {n.name + ':' + n.version}
                                                            </Select.Option>
                                                        ))
                                                    }
                                                </Select>
                                                <Button onClick={this.handleAddAPIGateway}>添加API网关</Button>
                                            </div>
                                        )
                                        : (
                                            <div>
                                                <Button onClick={this.handleDeleteAPIGateway}>删除API网关</Button>
                                            </div>
                                        )
                                }
                                </div>
                            </div>
                        );
                    })()}
                </Drawer>
            </div>
        );
    }
};

export default connect(({ namespace, repo }) => ({
    namespace,
    repo: repo.gatewayRepo
}))(NamespaceList);

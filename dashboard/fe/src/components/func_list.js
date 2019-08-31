import React from 'react';
import {
    Table,
    Tag,
    Button,
    Popover,
    Statistic,
    Row,
    Col,
    Drawer,
    Descriptions,
    Divider
} from 'antd';
import { connect } from 'react-redux';
import {
    downFunc,
    fetchFuncList,
    intervalFuncListFetch,
    intervalFuncListUnsetHandler,
    funcDetailFetch,

    FUNC_DETAIL_SET
} from '../actions/func';

import {
    NAMESPACE_SELECTED_SET
} from '../actions/namespace';

class FuncList extends React.Component {

    FRESH_INTERVAL = 5000;

    state = {
        funcDetailVisible: false
    };

    constructor(props) {
        super(props);

        if (this.props.namespaceSelected === NAMESPACE_SELECTED_SET) {
            this.props.dispatch(fetchFuncList(this.props.namespace));
            this.props.dispatch(intervalFuncListFetch(this.props.namespace, this.FRESH_INTERVAL));
        }
    }

    shouldComponentUpdate(nextProps, nextState) {
        if (this.props.namespace !== nextProps.namespace) {
            this.props.dispatch(intervalFuncListUnsetHandler());
            this.props.dispatch(fetchFuncList(nextProps.namespace));
            this.props.dispatch(intervalFuncListFetch(nextProps.namespace, this.FRESH_INTERVAL));
        }

        if (this.props.func.funcDetailState !== FUNC_DETAIL_SET
           && nextProps.func.funcDetailState === FUNC_DETAIL_SET) {
           nextState.funcDetailVisible = true;
       }

        return true;
    }

    componentWillUnmount() {
        this.props.dispatch(intervalFuncListUnsetHandler());
    }

    funcDetailDrawerOnClose = () => this.setState({ funcDetailVisible: false });

    render() {
        const COLUMNS = [
            {
                title: '名称',
                dataIndex: 'funcName',
                key: 'funcName'
            },
            {
                title: '命名空间',
                dataIndex: 'funcNamespace',
                key: 'funcNamespace'
            },
            {
                title: '状态性',
                key: 'funcStateful',
                render: n => ((() => {
                    if (n.stateful) {
                        return (<Tag key='y'>有状态</Tag>);
                    }
                    else {
                        return (<Tag key='n'>无状态</Tag>);
                    }
                })())
            },
            {
                title: '弹性伸缩',
                key: 'funcAutoscaling',
                render: n => (() => {
                    if (n.funcAutoscalingInfo === null) {
                        return (<Tag key='n'>无</Tag>);
                    }
                    else {
                        return (
                            <Popover
                                title='弹性伸缩详情'
                                trigger='hover'
                                content={(
                                    <Row gutter={24} style={{ width: 300 }}>
                                        <Col span={8}>
                                            <Statistic
                                                title='CPU'
                                                value={n.funcAutoscalingInfo.cpu}
                                                suffix='%' />
                                        </Col>
                                        <Col span={8}>
                                            <Statistic
                                                title='最小Pod数'
                                                value={n.funcAutoscalingInfo.min} />
                                        </Col>
                                        <Col span={8}>
                                            <Statistic
                                                title='最大Pod数'
                                                value={n.funcAutoscalingInfo.max} />
                                        </Col>
                                    </Row>
                                )}>
                                <Tag key='y'>有</Tag>
                            </Popover>
                        );
                    }
                })()
            },
            {
                title: '镜像',
                key: 'funcImage',
                dataIndex: 'funcImage'
            },
            {
                title: '副本数(可用/不可用)',
                key: 'funcReplicas',
                render: n => (
                    <span>
                        { n.funcReplicas }
                        (
                        { n.funcAvailableReplicas }
                        /
                        { n.funcUnavailableReplicas }
                        )
                    </span>
                )
            },
            {
                title: '操作',
                key: 'operation',
                render: n => (
                    <span>
                        <Button
                            onClick={() => this.props.dispatch(funcDetailFetch(n.funcNamespace, n.funcName, n.stateful))}
                            size='small'
                            style={{ marginRight: 8 }}>详情</Button>
                        <Button
                            onClick={() => this.props.dispatch(downFunc(n.funcNamespace, n.funcName))}
                            size='small'
                            style={{ marginRight: 8 }}>删除</Button>
                    </span>
                )
            }
        ];

        const FUNC_DETAIL_COLUMNS = [
            {
                title: '名称',
                key: 'name',
                dataIndex: 'name'
            },
            {
                title: '命名空间',
                key: 'namespace',
                dataIndex: 'namespace'
            },
            {
                title: '状态',
                key: 'status',
                dataIndex: 'status'
            },
            {
                title: '应用镜像',
                key: 'image',
                dataIndex: 'imageTag'
            },
            {
                title: '所在宿主机',
                key: 'node',
                dataIndex: 'node'
            },
            {
                title: '镜像拉取策略',
                key: 'policy',
                dataIndex: 'policy'
            }
        ];

        let dataSource = [];
        this.props.func.func.map(n => dataSource.push({
            key: n.name,
            funcName: n.name,
            funcNamespace: n.namespace,
            funcImage: n.imageTag,
            funcReplicas: n.replicas,
            funcAvailableReplicas: n.available,
            funcUnavailableReplicas: n.unavailable,
            funcAutoscalingInfo: n.autoscalingInfo
        }));

        return (
            <div>
                <Table columns={COLUMNS} dataSource={dataSource} />
                <Drawer
                    title={
                        this.props.func.funcDetailState === FUNC_DETAIL_SET
                            ? this.props.func.funcDetail.common.name + " 详细信息"
                            : '未知函数'
                    }
                    visible={this.state.funcDetailVisible}
                    width={840}
                    onClose={this.funcDetailDrawerOnClose}>

                    <Descriptions title="函数服务基本信息">
                        <Descriptions.Item label="函数服务">
                            {
                                this.props.func.funcDetailState === FUNC_DETAIL_SET
                                    ? this.props.func.funcDetail.common.name
                                    : '未知'
                            }
                        </Descriptions.Item>
                        <Descriptions.Item label="命名空间">
                            {
                                this.props.func.funcDetailState === FUNC_DETAIL_SET
                                    ? this.props.func.funcDetail.common.namespace
                                    : '未知'
                            }
                        </Descriptions.Item>
                        <Descriptions.Item label="应用镜像">
                            {
                                this.props.func.funcDetailState === FUNC_DETAIL_SET
                                    ? this.props.func.funcDetail.common.imageTag
                                    : '未知'
                            }
                        </Descriptions.Item>
                        <Descriptions.Item label="副本数">
                            {
                                this.props.func.funcDetailState === FUNC_DETAIL_SET
                                    ? this.props.func.funcDetail.common.replicas
                                    : '未知'
                            }
                        </Descriptions.Item>
                        <Descriptions.Item label="可用副本数">
                            {
                                this.props.func.funcDetailState === FUNC_DETAIL_SET
                                    ? this.props.func.funcDetail.common.available
                                    : '未知'
                            }
                        </Descriptions.Item>
                        <Descriptions.Item label="不可用副本数">
                            {
                                this.props.func.funcDetailState === FUNC_DETAIL_SET
                                    ? this.props.func.funcDetail.common.unavailable
                                    : '未知'
                            }
                        </Descriptions.Item>
                    </Descriptions>

                    <Divider />
                    <h3>Pod信息</h3>
                    <Table columns={FUNC_DETAIL_COLUMNS} dataSource={
                            this.props.func.funcDetailState === FUNC_DETAIL_SET
                                ? this.props.func.funcDetail.pods
                                : []
                    } />
                </Drawer>
            </div>
        );
    }
};

export default connect(({ func, namespace }) => ({
    func,
    namespaceSelected: namespace.selectedState,
    namespace: namespace.selectedNamespace
}))(FuncList);

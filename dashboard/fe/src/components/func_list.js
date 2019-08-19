import React from 'react';
import { Table, Tag, Button, Popover, Statistic, Row, Col } from 'antd';
import { connect } from 'react-redux';
import {
    fetchFuncList,
    intervalFuncListFetch,
    intervalFuncListUnsetHandler
} from '../actions/func';

import {
    NAMESPACE_SELECTED_SET
} from '../actions/namespace';

class FuncList extends React.Component {

    FRESH_INTERVAL = 5000;

    constructor(props) {
        super(props);

        if (this.props.namespaceSelected === NAMESPACE_SELECTED_SET) {
            this.props.dispatch(fetchFuncList(this.props.namespace));
            this.props.dispatch(intervalFuncListFetch(this.props.namespace, this.FRESH_INTERVAL));
        }
    }

    shouldComponentUpdate(nextProps, nextState) {
        if (this.props.namespace !== nextProps.namespace) {
            if (this.props.namespaceSelected === NAMESPACE_SELECTED_SET) {
                this.props.dispatch(fetchFuncList(this.props.namespace));
            }
            this.props.dispatch(intervalFuncListUnsetHandler());
            this.props.dispatch(fetchFuncList(nextProps.namespace));
            this.props.dispatch(intervalFuncListFetch(nextProps.namespace, this.FRESH_INTERVAL));
        }

        return true;
    }

    componentWillUnmount() {
        this.props.dispatch(intervalFuncListUnsetHandler());
    }

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
                        <Button size='small' style={{ marginRight: 8 }}>详情</Button>
                        <Button size='small' style={{ marginRight: 8 }}>删除</Button>
                    </span>
                )
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

        return (<Table columns={COLUMNS} dataSource={dataSource} />);
    }
};

export default connect(({ func, namespace }) => ({
    func,
    namespaceSelected: namespace.selectedState,
    namespace: namespace.selectedNamespace
}))(FuncList);

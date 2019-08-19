import React from 'react';
import { Table, Tag, Button } from 'antd';
import { connect } from 'react-redux';
import {
    fetchFuncList,
    FUNC_LIST_UNSET
} from '../actions/func';

import {
    NAMESPACE_SELECTED_SET
} from '../actions/namespace';

class FuncList extends React.PureComponent {

    state = {
        namespace: '',
        waitingFresh: false
    };

    FRESH_INTERVAL = 1000;

    constructor(props) {
        super(props);

        if (this.props.state === FUNC_LIST_UNSET
           && this.props.namespaceSelected === NAMESPACE_SELECTED_SET) {
            this.props.dispatch(fetchFuncList(this.props.namespace));
            this.setState({ namespace: this.props.namespace });
        };
    }

    render() {
        
        if (this.state.waitingFresh === false
            && this.props.namespaceSelected === NAMESPACE_SELECTED_SET) {
            this.setState({ waitingFresh: true });
            setTimeout(() => {
                this.props.dispatch(fetchFuncList(this.props.namespace));
                this.setState({ waitingFresh: false });
            }, this.FRESH_INTERVAL);
        }
        if (this.props.namespaceSelected === NAMESPACE_SELECTED_SET
           && this.state.namespace !== this.props.namespace) {
            this.props.dispatch(fetchFuncList(this.props.namespace));
            this.setState({ namespace: this.props.namespace });
        }

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
            funcUnavailableReplicas: n.unavailable
        }));

        return (<Table columns={COLUMNS} dataSource={dataSource} />);
    }
};

export default connect(({ func, namespace }) => ({
    func,
    namespaceSelected: namespace.selectedState,
    namespace: namespace.selectedNamespace
}))(FuncList);

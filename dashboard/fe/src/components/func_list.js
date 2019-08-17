import React from 'react';
import { Table, Tag } from 'antd';
import { connect } from 'react-redux';
import {
    fetchFunc,
    FUNC_LIST_UNSET
} from '../actions/func';

import {
    NAMESPACE_SELECTED_SET
} from '../actions/namespace'

class FuncList extends React.PureComponent {

    state = {
        namespace: ''
    };

    constructor(props) {
        super(props);

        if (this.props.state === FUNC_LIST_UNSET
           && this.props.namespaceSelected === NAMESPACE_SELECTED_SET) {
            this.props.dispatch(fetchFunc(this.props.namespace));
            this.setState({ namespace: this.props.namespace });
        };
    }

    render() {
        const COLUMNS = [
            {
                title: '函数服务名称',
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
                title: '引用镜像',
                key: 'funcImage',
                dataIndex: 'funcImage'
            },
            {
                title: '副本数/可用副本/不可用副本',
                key: 'funcReplicas',
                render: n => (
                    <span>
                        { n.funcReplicas }
                        /
                        { n.funcAvailableReplicas }
                        /
                        { n.funcUnavailableReplicas }
                    </span>
                )
            }
        ];

        if (this.props.namespaceSelected === NAMESPACE_SELECTED_SET
           && this.state.namespace !== this.props.namespace) {
            this.props.dispatch(fetchFunc(this.props.namespace));
            this.setState({ namespace: this.props.namespace });
        }

        let dataSource = [];
        this.props.func.func.map(n => dataSource.push({
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

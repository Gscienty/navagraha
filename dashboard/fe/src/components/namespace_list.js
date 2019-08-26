import React from 'react';
import { Table, Tag, Button } from 'antd';
import { connect } from 'react-redux';
import {
    selectDisplayNamespace,
    fetchNamespaces,
    deleteNamespace,
    NAMESPACE_LIST_SET,
    NAMESPACE_LIST_UNSET,
    NAMESPACE_SELECTED_SET
} from '../actions/namespace';


class NamespaceList extends React.PureComponent {

    state = {
        waitingFresh: false,
    };

    FRESH_INTERVAL = 1000;

    constructor(props) {
        super(props);

        if (this.props.namespace.state === NAMESPACE_LIST_UNSET
            || this.props.namespace.namespace.find(n => n.status !== 'Active')) {
            this.props.dispatch(fetchNamespaces());
        }
    }

    render() {
        if (this.state.waitingFresh === false) {
            this.setState({ waitingFresh: true }); // TODO
            setTimeout(() => {
                this.props.dispatch(fetchNamespaces());
                this.setState({ waitingFresh: false });
            }, this.FRESH_INTERVAL);
        };

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
                title: '操作',
                key: 'operation',
                render: n => (
                    <div>
                        {(() => {
                            if (this.props.namespace.selectedState === NAMESPACE_SELECTED_SET
                               && this.props.namespace.selectedNamespace === n.namespaceName) {
                                return (
                                    <Tag key={n.namespaceName} closable={false} color='#108ee9'>已选择</Tag>
                                )
                            }
                            if (n.namespaceStatus === 'Terminating') {
                                return (
                                    <Tag key={n.namespaceName} closable={false} color='#f50'>移除中...</Tag>
                                )
                            }
                            else {
                                return (
                                    <div>
                                        <Button
                                        type='primary'
                                        size='small'
                                        onClick={() => this.props.dispatch(selectDisplayNamespace(n.namespaceName))}>
                                        选择
                                        </Button>

                                        &nbsp;

                                        <Button size='small' onClick={() => this.props.dispatch(deleteNamespace(n.namespaceName))}>删除</Button>
                                    </div>
                                );
                            }
                        })()}
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
                namespaceStatus: n.status
            }));
        };

        return (<Table columns={COLUMNS} dataSource={dataSource} />);
    }
};

export default connect(({ namespace }) => ({
    namespace
}))(NamespaceList);

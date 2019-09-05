import React from 'react';
import {
    Table
} from 'antd';
import { connect } from 'react-redux';

import {
    fetchNodeList,

    NODE_LIST_UNSET
} from '../actions/node';


class NodeList extends React.PureComponent {

    constructor(props) {
        super(props);

        if (this.props.node.state === NODE_LIST_UNSET) {
            this.props.dispatch(fetchNodeList());
        }
    }

    COLUMNS = [
        {
            title: "名称",
            dataIndex: "name",
            key: "name"
        },
        {
            title: "状态",
            dataIndex: "status",
            key: "status"
        },
        {
            title: "体系结构",
            dataIndex: "architecture",
            key: "architecture"
        },
        {
            title: "容器运行环境",
            dataIndex: "containerRuntimeVersion",
            key: "containerRuntimeVersion"
        },
        {
            title: "内核版本",
            dataIndex: "kernelVersion",
            key: "kernelVersion"
        },
        {
            title: "操作系统",
            dataIndex: "os",
            key: "os"
        },
    ];

    render() {
        return (
            <Table columns={this.COLUMNS} dataSource={this.props.node.nodes} />
        );
    }
};

export default connect(({
    node
}) => ({
    node
}))(NodeList);
